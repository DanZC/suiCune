#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "network.h"
#include "json.h"
#include "assets.h"
#include "../home/delay.h"

/// WIP experimental networking system to replace SDLNet.
/// To enable it, set USE_SDLNET to 0
#define USE_SDLNET 1

#if defined(NETWORKING_SUPPORT)
#if USE_SDLNET
#if defined(_MSC_VER)
#include <SDL_NET.h>
#else
#include <SDL2/SDL_net.h>
#endif
#else
#if defined(_MSC_VER)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <stdlib.h>
#include <memory.h>
#endif
#include "../tools/emu/peanut_gb.h"
#include "../lib/libmobile/mobile.h"
#include "socket.h"
extern struct gb_s gb;

#if !(defined(__cplusplus) || defined(_MSC_VER))
#define static_assert _Static_assert
#endif

#ifdef _MSC_VER
#ifndef _SSIZE_T_DEFINED
#ifdef _WIN64
typedef __int64 ssize_t;
#else
typedef int ssize_t;
#endif
#define _SSIZE_T_DEFINED
#endif
#endif

#define UDP_PORT 22600
#define TCP_PORT 22601
#define MOBILE_PORT 22602

#define UDP_PACKET_SIZE 32

bool gNetworkingInit = false;
#if USE_SDLNET
static UDPsocket host;
static UDPpacket* packet;
static TCPsocket serial;
static TCPsocket cserial;
static TCPsocket linkSocket;
static SDLNet_SocketSet sockets;
static IPaddress localhost;
#else
struct network_packet {
    uint8_t* buffer;
    struct mobile_addr sender;
    int len;
};

struct network_data {
    SOCKET udp;
    struct network_packet udp_packet;
    SOCKET serial;
    SOCKET linkSocket;
    struct mobile_addr linkAddr;
};

static struct network_data gNetworkData;
#endif
static uint32_t hostUniqueId;

static LANClient gLANClientCandidates[16];
static uint32_t gLANClientCandidateCount;

uint8_t gOtherPlayerGender;

// A networking interface for suiCune. Supports both LAN (local) connections, emulating
// the standard link cable connection, and internet (remote) connections, emulating
// the mobile GB connection.
// Mobile connections use the libmobile library.

//// LAN connections (link cable multiplayer)
// Standard multiplayer features of Pokemon Crystal used the standard link cable,
// which allowed two gameboy systems to connect to each other. suiCune emulates
// this functionality using network sockets, allowing devices on a LAN to connect
// to each other. However, the interface presented to the player must be modified
// to accomadate this change.
//
// In order to connect to players using the "link cable" the player must be connected to
// the same access point as the player they want to connect to.
// Connection begins by opening a UDP port. The player can choose to host or join a room.
// When hosting a room, a CMD_HOST_LAN packet is sent via a broadcast address to all devices
// connected to the LAN. If the other player is looking to join a room, they will receive the
// packet and the host's name, id no., and in-game gender will be displayed. This allows two players
// with the same name to be differentiated.
// The joining player will then select which LAN partner they wish to connect to, from a list of available
// rooms being hosted. A CMD_JOIN_LAN packet will be sent back to the host. The host will receive the 
// packet and the joining player's name, id no., and in-game gender. If the host accepts the connection, 
// they will send their IP address and try to establish a TCP connection with the joiner. 
// Once established, the emulation layer will send all serial communication through the TCP port.
//
// This setup allows devices to communicate with each other without the need to physically connect together 
// like what was required with the original gameboy. A similar system is used for Pokemon games using wireless
// communication, with the Wireless Adapater for Pokemon FireRed and LeafGreen and the DS/3DS wireless 
// communications for Pokemon Generation IV and onwards being prime examples. This also forgos needing
// to know the IP address of devices you wish connect, as device discovery is accomplished as part of
// the connection process.

//// Internet connections (mobile adapter multiplayer)
// Pokemon Crystal made use of a mobile adapter that allowed one to connect their Gameboy to a cell phone
// and connect to the internet through the phone. This feature was only available in the Japanese
// version, since the adapter never made it out of Japan. However, we can simulate the adapter
// using modern internet technologies and thus restore the lost functionality of the adapter,
// including online multiplayer.

enum {
    CMD_HOST_LAN,
    CMD_JOIN_LAN,
    CMD_ACCEPT_JOIN_LAN,
    CMD_DISCONNECT_LAN,
    CMD_HOST_MOBILE,
    CMD_JOIN_MOBILE,
    CMD_ACCEPT_JOIN_MOBILE,
    CMD_DISCONNECT_MOBILE,
};

typedef enum {
    NETSTATE_NOTHING,
    NETSTATE_HOSTING,
    NETSTATE_JOINING,
    NETSTATE_LAN_HOST,
    NETSTATE_LAN_CLIENT,
} netstate_e;

netstate_e gNetworkState;

typedef struct CmdPacket {
    uint32_t uid;
    uint8_t type;
    union {
        struct {
            uint16_t trainerId;
            uint8_t name[11];
            uint8_t gender;
        } host_lan;
        struct {
            uint16_t trainerId;
            uint8_t name[11];
            uint8_t gender;
        } join_lan;
    };
} CmdPacket_s;

static_assert(sizeof(CmdPacket_s) <= UDP_PACKET_SIZE, "");

static void gb_serial_tx_test(const uint8_t x);
static enum gb_serial_rx_ret_e gb_serial_rx_test(uint8_t* x);

#define MAX_TRIES_DETECT_PACKET_SENT 32

// socket implementations "borrowed" from libmobile-bgb
union u_sockaddr {
    struct sockaddr addr;
    struct sockaddr_in addr4;
    struct sockaddr_in6 addr6;
};

static struct sockaddr *convert_sockaddr(socklen_t *addrlen, union u_sockaddr *u_addr, const struct mobile_addr *addr)
{
    if (!addr) {
        *addrlen = 0;
        return NULL;
    } else if (addr->type == MOBILE_ADDRTYPE_IPV4) {
        const struct mobile_addr4 *addr4 = (struct mobile_addr4 *)addr;
        memset(&u_addr->addr4, 0, sizeof(u_addr->addr4));
        u_addr->addr4.sin_family = AF_INET;
        u_addr->addr4.sin_port = htons(addr4->port);
        if (sizeof(struct in_addr) != sizeof(addr4->host)) return NULL;
        memcpy(&u_addr->addr4.sin_addr.s_addr, addr4->host,
            sizeof(struct in_addr));
        *addrlen = sizeof(struct sockaddr_in);
        return &u_addr->addr;
    } else if (addr->type == MOBILE_ADDRTYPE_IPV6) {
        const struct mobile_addr6 *addr6 = (struct mobile_addr6 *)addr;
        memset(&u_addr->addr6, 0, sizeof(u_addr->addr6));
        u_addr->addr6.sin6_family = AF_INET6;
        u_addr->addr6.sin6_port = htons(addr6->port);
        if (sizeof(struct in6_addr) != sizeof(addr6->host)) return NULL;
        memcpy(&u_addr->addr6.sin6_addr.s6_addr, addr6->host,
            sizeof(struct in6_addr));
        *addrlen = sizeof(struct sockaddr_in6);
        return &u_addr->addr;
    } else {
        *addrlen = 0;
        return NULL;
    }
}

struct mobile_addr make_mobile_addr(enum mobile_addrtype addrtype, uint32_t host, unsigned bindport) {
    struct mobile_addr addr;
    addr.type = addrtype;
    switch(addrtype) {
        case MOBILE_ADDRTYPE_IPV4: {
            struct mobile_addr4* addr4 = (struct mobile_addr4*)&addr;
            addr4->host[0] = host & 0xff;
            addr4->host[1] = (host >> 8) & 0xff;
            addr4->host[2] = (host >> 16) & 0xff;
            addr4->host[3] = (host >> 24) & 0xff;
            addr4->port = bindport;
        } break;
        case MOBILE_ADDRTYPE_IPV6: {
            struct mobile_addr6* addr6 = (struct mobile_addr6*)&addr;
            addr6->host[0] = host & 0xff;
            addr6->host[1] = (host >> 8) & 0xff;
            addr6->host[2] = (host >> 16) & 0xff;
            addr6->host[3] = (host >> 24) & 0xff;
            // TODO: Finish this
            addr6->port = bindport;
        } break;
        default: assert(false);
    }
    return addr;
}

SOCKET socket_open(enum mobile_socktype type, enum mobile_addrtype addrtype, unsigned bindport) {
    int sock_type;
    switch (type) {
        case MOBILE_SOCKTYPE_TCP: sock_type = SOCK_STREAM; break;
        case MOBILE_SOCKTYPE_UDP: sock_type = SOCK_DGRAM; break;
        default: assert(false); return INVALID_SOCKET;
    }

    int sock_addrtype;
    switch (addrtype) {
        case MOBILE_ADDRTYPE_IPV4: sock_addrtype = AF_INET; break;
        case MOBILE_ADDRTYPE_IPV6: sock_addrtype = AF_INET6; break;
        default: assert(false); return false;
    }

    SOCKET sock = socket(sock_addrtype, sock_type, 0);
    if (sock == INVALID_SOCKET) {
        socket_perror("socket");
        return INVALID_SOCKET;
    }
    if (socket_setblocking(sock, 0) == -1) {
        socket_close(sock);
        return INVALID_SOCKET;
    }

    // Set SO_REUSEADDR so that we can bind to the same port again after
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
            (char *)&(int){1}, sizeof(int)) == SOCKET_ERROR) {
        socket_perror("setsockopt");
        socket_close(sock);
        return INVALID_SOCKET;
    }

    #ifdef SO_BROADCAST
    // Allow LAN broadcasts with the socket
    if(type == MOBILE_SOCKTYPE_UDP)
    {
        if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, 
                (char *)&(int){1}, sizeof(int)) == SOCKET_ERROR) {
            socket_perror("setsockopt");
            socket_close(sock);
            return INVALID_SOCKET;
        }
    }
    #endif

    // Set TCP_NODELAY to aid sending packets inmediately, reducing latency
    if (type == MOBILE_SOCKTYPE_TCP &&
            setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,
                (char *)&(int){1}, sizeof(int)) == SOCKET_ERROR) {
        socket_perror("setsockopt");
        socket_close(sock);
        return INVALID_SOCKET;
    }

    int rc;
    if (addrtype == MOBILE_ADDRTYPE_IPV4) {
        struct sockaddr_in addr = {
            .sin_family = AF_INET,
            .sin_port = htons(bindport),
        };
        rc = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    } else {
        struct sockaddr_in6 addr = {
            .sin6_family = AF_INET6,
            .sin6_port = htons(bindport),
        };
        rc = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    }
    if (rc == SOCKET_ERROR) {
        socket_perror("bind");
        socket_close(sock);
        return INVALID_SOCKET;
    }

    return sock;
}

bool socket_listen(SOCKET sock)
{
    assert(sock != INVALID_SOCKET);

    if (listen(sock, 1) == SOCKET_ERROR) {
        socket_perror("listen");
        return false;
    }

    return true;
}

SOCKET socket_accept(SOCKET sock)
{
    assert(sock != INVALID_SOCKET);

    if (socket_hasdata(sock) <= 0) return INVALID_SOCKET;
    SOCKET newsock = accept(sock, NULL, NULL);
    if (newsock == INVALID_SOCKET) {
        socket_perror("accept");
        return INVALID_SOCKET;
    }
    if (socket_setblocking(newsock, 0) == -1) return INVALID_SOCKET;

    socket_close(sock);
    return newsock;
}

int socket_connect_ip(SOCKET sock, const struct mobile_addr *addr)
{
    assert(sock != INVALID_SOCKET);

    union u_sockaddr u_addr;
    socklen_t sock_addrlen;
    struct sockaddr *sock_addr = convert_sockaddr(&sock_addrlen, &u_addr, addr);

    // Try to connect/check if we're connected
    int rc = connect(sock, sock_addr, sock_addrlen);
    int err = socket_geterror();
    if (rc != SOCKET_ERROR) return 1;

    // If the connection is in progress, try again in a bit.
    // On windows, connect() returns EISCONN rather than no error.
    if (err == SOCKET_EWOULDBLOCK ||
            err == SOCKET_EINPROGRESS ||
            err == SOCKET_EALREADY) {
        return 0;
    }
// Windows will return WSAEINVAL when calling connect with a pending socket.
// A dirty, but sufficient workaround is to treat WSAEINVAL the same as the other
// "in progress" error codes.
#if _WIN32
    if (err == WSAEINVAL) return 0;
#endif
    if (err == SOCKET_EISCONN) return 1;

    char sock_str[SOCKET_STRADDR_MAXLEN] = {0};
    socket_straddr(sock_str, sizeof(sock_str), sock_addr, sock_addrlen);
    socket_seterror(err);
    fprintf(stderr, "Could not connect (%s): ", sock_str);
    socket_perror(NULL);
    return -1;
}

int socket_send(SOCKET sock, const void *data, const unsigned size, const struct mobile_addr *addr)
{
    assert(sock != INVALID_SOCKET);

    union u_sockaddr u_addr;
    socklen_t sock_addrlen;
    struct sockaddr *sock_addr = convert_sockaddr(&sock_addrlen, &u_addr, addr);

    ssize_t len = sendto(sock, data, size, 0, sock_addr, sock_addrlen);
    if (len == SOCKET_ERROR) {
        // If the socket is blocking, we just haven't sent anything
        int err = socket_geterror();
        if (err == SOCKET_EWOULDBLOCK) return 0;

        socket_perror("send");
        return -1;
    }
    return (int)len;
}

int socket_recv(SOCKET sock, void *data, unsigned size, struct mobile_addr *addr)
{
    assert(sock != INVALID_SOCKET);

    // Make sure at least one byte is in the buffer
    if (socket_hasdata(sock) <= 0) return 0;

    union u_sockaddr u_addr = {0};
    socklen_t sock_addrlen = sizeof(u_addr);
    struct sockaddr *sock_addr = (struct sockaddr *)&u_addr;

    ssize_t len;
    if (data) {
        // Retrieve at least 1 byte from the buffer
        len = recvfrom(sock, data, size, 0, sock_addr, &sock_addrlen);
    } else {
        // Check if at least 1 byte is available in buffer
        char c;
        len = recvfrom(sock, &c, 1, MSG_PEEK, sock_addr, &sock_addrlen);
    }
    if (len == SOCKET_ERROR) {
        // If the socket is nonblocking, we just haven't received anything.
        // Though this shouldn't happen thanks to the socket_hasdata check.
        if (socket_geterror() == SOCKET_EWOULDBLOCK) return 0;
        socket_perror("recv");
        return -1;
    }

    // A length of 0 will be returned if the remote has disconnected.
    if (len == 0) {
        // Though it's only relevant to TCP sockets, as UDP sockets may receive
        // zero-length datagrams.
        int sock_type = 0;
        socklen_t sock_type_len = sizeof(sock_type);
        if (getsockopt(sock, SOL_SOCKET, SO_TYPE, (char *)&sock_type,
                &sock_type_len) == SOCKET_ERROR) {
            socket_perror("getsockopt");
            return -1;
        }
        if (sock_type == SOCK_STREAM) return -2;
    }

    if (!data) return 0;

    if (addr && sock_addrlen) {
        if (sock_addr->sa_family == AF_INET) {
            struct mobile_addr4 *addr4 = (struct mobile_addr4 *)addr;
            addr4->type = MOBILE_ADDRTYPE_IPV4;
            addr4->port = ntohs(u_addr.addr4.sin_port);
            memcpy(addr4->host, &u_addr.addr4.sin_addr.s_addr,
                sizeof(addr4->host));
        } else if (sock_addr->sa_family == AF_INET6) {
            struct mobile_addr6 *addr6 = (struct mobile_addr6 *)addr;
            addr6->type = MOBILE_ADDRTYPE_IPV6;
            addr6->port = ntohs(u_addr.addr6.sin6_port);
            memcpy(addr6->host, &u_addr.addr6.sin6_addr.s6_addr,
                sizeof(addr6->host));
        }
    }

    return (int)len;
}

#if !USE_SDLNET
bool NetworkStart(void) {
#if defined(_WIN32)
    /* Start up the windows networking */
    WORD version_wanted = MAKEWORD(1,1);
    WSADATA wsaData;

    if ( WSAStartup(version_wanted, &wsaData) != 0 ) {
        return false;
    }
#else
    /* SIGPIPE is generated when a remote socket is closed */
    void (*handler)(int);
    handler = signal(SIGPIPE, SIG_IGN);
    if ( handler != SIG_DFL ) {
        signal(SIGPIPE, handler);
    }
#endif
    return true;
}
#endif

bool Network_ResolveHost(const char* hostname, const char* port, struct mobile_addr* addr);
#define _s_impl(x) #x
#define _s(x) _s_impl(x)

bool NetworkInit(void) {
#if USE_SDLNET
    if (SDLNet_Init() < 0) {
        printf("An error occurred while initializing SDL_Net.\n");
        return false;
    }
    else {
        printf("Initialized SDLNet library.\n");
        host = SDLNet_UDP_Open(UDP_PORT);
        // localhost = SDLNet_UDP_GetPeerAddress(host, -1);
        SDLNet_ResolveHost(&localhost, "localhost", UDP_PORT);
        packet = SDLNet_AllocPacket(UDP_PACKET_SIZE);
        packet->maxlen = UDP_PACKET_SIZE;
        packet->address.host = INADDR_ANY;
        packet->address.port = htons(UDP_PORT);

        sockets = SDLNet_AllocSocketSet(1);

        hostUniqueId = (uint32_t)rand() + (uint32_t)time(NULL);
        printf("Unique id: %d\n", hostUniqueId);
        gNetworkingInit = true;
        gNetworkState = NETSTATE_NOTHING;
        gb.gb_serial_rx = gb_serial_rx_test;
        gb.gb_serial_tx = gb_serial_tx_test;
        return true;
    }
#else 
    if(!NetworkStart()) {
        printf("An error occurred while initializing networking.\n");
        return false;
    }

    struct network_data* state = &gNetworkData;

    state->udp = socket_open(MOBILE_SOCKTYPE_UDP, MOBILE_ADDRTYPE_IPV4, UDP_PORT);
    if(state->udp == INVALID_SOCKET)
        return false;

    if(!Network_ResolveHost("localhost", _s(UDP_PORT), &state->udp_packet.sender)) {
        socket_close(state->udp);
        state->udp = INVALID_SOCKET;
        return false;
    }

    state->udp_packet.buffer = malloc(UDP_PACKET_SIZE);
    memset(state->udp_packet.buffer, 0, UDP_PACKET_SIZE);
    state->linkSocket = INVALID_SOCKET;
    memset(&state->linkAddr, 0, sizeof(state->linkAddr));
    state->serial = INVALID_SOCKET;
    hostUniqueId = (uint32_t)rand() + (uint32_t)time(NULL);
    printf("Unique id: %d\n", hostUniqueId);
    gNetworkingInit = true;
    gNetworkState = NETSTATE_NOTHING;
    gb.gb_serial_rx = gb_serial_rx_test;
    gb.gb_serial_tx = gb_serial_tx_test;
    return true;
#endif
}

#if !USE_SDLNET
int recv_packet(SOCKET sock, struct network_packet* packet) {
    int size = socket_recv(sock, packet->buffer, UDP_PACKET_SIZE, &packet->sender);
    if(size < 0)
        return -1;
    if(size == 0)
        return 0;
    packet->len = size;
    return 1;
}
#endif

void gb_serial_tx(const uint8_t x) {
    // send byte
    printf("Send: $%02x\n", x);
#if USE_SDLNET
    SDLNet_TCP_Send(linkSocket, &x, sizeof(x));
#else
    struct network_data* state = &gNetworkData;
    socket_send(state->linkSocket, &x, sizeof(x), &state->linkAddr);
#endif
}

enum gb_serial_rx_ret_e gb_serial_rx(uint8_t* x) {
    // receive byte
#if USE_SDLNET
    int ready = SDLNet_CheckSockets(sockets, 0);
    if(ready < 0) {
        printf("Error: %s\n", SDLNet_GetError());
        return GB_SERIAL_RX_NO_CONNECTION;
    }
    else if(ready == 0) {
        return GB_SERIAL_RX_NO_CONNECTION;
    }
    int bytes = SDLNet_TCP_Recv(linkSocket, x, 1);
    if(bytes == 0) {
        return GB_SERIAL_RX_NO_CONNECTION;
    }
    else if(bytes < 0) {
        printf("Error: %s\n", SDLNet_GetError());
        return GB_SERIAL_RX_NO_CONNECTION;
    }
#else
    struct network_data* state = &gNetworkData;
    int ready = socket_hasdata(state->linkSocket);
    if(ready < 0) {
        // printf("Error: %s\n", SDLNet_GetError());
        return GB_SERIAL_RX_NO_CONNECTION;
    }
    else if(ready == 0) {
        return GB_SERIAL_RX_NO_CONNECTION;
    }
    int bytes = socket_recv(state->linkSocket, x, 1, &state->linkAddr);
    if(bytes == 0) {
        return GB_SERIAL_RX_NO_CONNECTION;
    }
    else if(bytes < 0) {
        // printf("Error: %s\n", SDLNet_GetError());
        return GB_SERIAL_RX_NO_CONNECTION;
    }
#endif
    printf("Recv: $%02x\n", *x);
    return GB_SERIAL_RX_SUCCESS;
}

#if USE_SDLNET
static void NetworkTossQueueingPackets(void) {
    // Toss any packets waiting.
    while(SDLNet_UDP_Recv(host, packet) == 1) {}
}
#else
static void NetworkTossQueueingPackets(struct network_data* state) {
    int err;
    for(err = socket_hasdata(state->udp); err > 0; err = socket_hasdata(state->udp)) {
        if(recv_packet(state->udp, &state->udp_packet) < 0)
            return;
    }
    if(err < 0)
        return;
    return;
}
#endif

bool NetworkBroadcastLAN(const uint8_t* name, uint16_t id, uint8_t gender) {
#if USE_SDLNET
    NetworkTossQueueingPackets();
    memset(packet->data, 0, UDP_PACKET_SIZE);
    CmdPacket_s* cmd = (CmdPacket_s*)packet->data;
    cmd->type = CMD_HOST_LAN;
    cmd->uid = htonl(hostUniqueId);
    memset(cmd->host_lan.name, 0x50, sizeof(cmd->host_lan.name));
    memcpy(cmd->host_lan.name, name, 10);
    cmd->host_lan.trainerId = htons(id);
    cmd->host_lan.gender = gender;
    packet->address.host = INADDR_BROADCAST;
    packet->len = sizeof(*cmd);
    packet->channel = 1;
    if(SDLNet_UDP_Send(host, -1, packet) == 0) {
        printf("Could not send UDP packet on port %d. Is the port blocked?\n", UDP_PORT);
        return false;
    }
    printf("Sent UDP packet on port %d.\n", UDP_PORT);
    if(gNetworkState != NETSTATE_HOSTING)
        gNetworkState = NETSTATE_HOSTING;
    return true;
#else
    struct network_data* state = &gNetworkData;
    NetworkTossQueueingPackets(state);

    struct network_packet* packet = &state->udp_packet;
    memset(packet->buffer, 0, UDP_PACKET_SIZE);
    CmdPacket_s* cmd = (CmdPacket_s*)packet->buffer;
    cmd->type = CMD_HOST_LAN;
    cmd->uid = htonl(hostUniqueId);
    memset(cmd->host_lan.name, 0x50, sizeof(cmd->host_lan.name));
    memcpy(cmd->host_lan.name, name, 10);
    cmd->host_lan.trainerId = htons(id);
    cmd->host_lan.gender = gender;
    packet->sender = make_mobile_addr(MOBILE_ADDRTYPE_IPV4, INADDR_BROADCAST, UDP_PORT);
    packet->len = sizeof(*cmd);
    if(socket_send(state->udp, packet->buffer, packet->len, &packet->sender) <= 0) {
        printf("Could not send UDP packet on port %d. Is the port blocked?\n", UDP_PORT);
        return false;
    }
    printf("Sent UDP packet on port %d.\n", UDP_PORT);
    if(gNetworkState != NETSTATE_HOSTING)
        gNetworkState = NETSTATE_HOSTING;
    return true;
#endif
}

void NetworkStartJoining(void) {
#if USE_SDLNET
    NetworkTossQueueingPackets();
#else
    struct network_data* state = &gNetworkData;
    NetworkTossQueueingPackets(state);
#endif
    gNetworkState = NETSTATE_JOINING;
}

bool NetworkTryJoinLAN(uint8_t which, const uint8_t* name, uint16_t id, uint8_t gender) {
    if(which < gLANClientCandidateCount) {
#if USE_SDLNET
        memset(packet->data, 0, UDP_PACKET_SIZE);
        CmdPacket_s* cmd = (CmdPacket_s*)packet->data;
        cmd->type = CMD_JOIN_LAN;
        cmd->uid = htonl(hostUniqueId);
        memset(cmd->host_lan.name, 0x50, sizeof(cmd->host_lan.name));
        memcpy(cmd->host_lan.name, name, 10);
        cmd->host_lan.trainerId = htons(id);
        cmd->host_lan.gender = gender;
        packet->address.host = gLANClientCandidates[which].address;
        packet->len = sizeof(CmdPacket_s);
        if(SDLNet_UDP_Send(host, -1, packet) == 0) {
            printf("Could not send UDP packet on port %d. Is the port blocked?\n", UDP_PORT);
            return false;
        }
        printf("Joining %d.%d.%d.%d...\n", 
            packet->address.host & 0xff, 
            (packet->address.host >> 8) & 0xff,
            (packet->address.host >> 16) & 0xff,
            (packet->address.host >> 24) & 0xff);
#else
        struct network_data* state = &gNetworkData;
        struct network_packet* packet = &gNetworkData.udp_packet;
        memset(packet->buffer, 0, UDP_PACKET_SIZE);
        CmdPacket_s* cmd = (CmdPacket_s*)packet->buffer;
        cmd->type = CMD_JOIN_LAN;
        cmd->uid = htonl(hostUniqueId);
        memset(cmd->host_lan.name, 0x50, sizeof(cmd->host_lan.name));
        memcpy(cmd->host_lan.name, name, 10);
        cmd->host_lan.trainerId = htons(id);
        cmd->host_lan.gender = gender;
        memcpy(packet->sender._addr4.host, &gLANClientCandidates[which].address, sizeof(packet->sender._addr4.host));
        packet->len = sizeof(CmdPacket_s);
        if(socket_send(state->udp, packet->buffer, packet->len, &packet->sender) <= 0) {
            printf("Could not send UDP packet on port %d. Is the port blocked?\n", UDP_PORT);
            return false;
        }
        printf("Joining %d.%d.%d.%d...\n", 
            packet->sender._addr4.host[0],
            packet->sender._addr4.host[1],
            packet->sender._addr4.host[2],
            packet->sender._addr4.host[3]);
#endif
        return true;
    }
    return false;
}

#if USE_SDLNET
bool NetworkTryRecvUDP(void) {
    int error = SDLNet_UDP_Recv(host, packet);
    if(error == -1) {
        printf("SDLNet: %s", SDLNet_GetError());
        return false;
    }
    return error == 1;
}
#endif

// Is this a duplicate of a host we already added?
static bool NetworkCheckDuplicateLANCandidate(uint32_t uid) {
    for(uint32_t i = 0; i < gLANClientCandidateCount; ++i) {
        if(gLANClientCandidates[i].uid == uid)
            return true;
    }
    return false;
}

#if USE_SDLNET
static void NetworkAddLANCandidate(void) {
    LANClient* lan = gLANClientCandidates + gLANClientCandidateCount;
    lan->address = packet->address.host;
    printf("Received packet from %d.%d.%d.%d\n", 
        lan->address & 0xff, 
        (lan->address >> 8) & 0xff,
        (lan->address >> 16) & 0xff,
        (lan->address >> 24) & 0xff);
    memset(lan->name, 0x50, sizeof(lan->name));
    CmdPacket_s* cmd = (CmdPacket_s*)packet->data;
    lan->uid = htonl(cmd->uid);
    memcpy(lan->name, cmd->host_lan.name, 10);
    lan->trainerId = htons(cmd->host_lan.trainerId);
    lan->gender = cmd->host_lan.gender;
    gLANClientCandidateCount++;
}
#else
static void NetworkAddLANCandidate(struct network_packet* packet) {
    LANClient* lan = gLANClientCandidates + gLANClientCandidateCount;
    lan->address = packet->sender._addr4.host[0] | 
        (packet->sender._addr4.host[1] << 8) |
        (packet->sender._addr4.host[2] << 16) |
        (packet->sender._addr4.host[3] << 24);
    printf("Received packet from %d.%d.%d.%d\n", 
        lan->address & 0xff, 
        (lan->address >> 8) & 0xff,
        (lan->address >> 16) & 0xff,
        (lan->address >> 24) & 0xff);
    memset(lan->name, 0x50, sizeof(lan->name));
    CmdPacket_s* cmd = (CmdPacket_s*)packet->buffer;
    lan->uid = htonl(cmd->uid);
    memcpy(lan->name, cmd->host_lan.name, 10);
    lan->trainerId = htons(cmd->host_lan.trainerId);
    lan->gender = cmd->host_lan.gender;
    gLANClientCandidateCount++;
}
#endif

#if USE_SDLNET
static bool NetworkTryAddLANCandidate(void) {
    CmdPacket_s* cmd = (CmdPacket_s*)packet->data;
    if(NetworkCheckDuplicateLANCandidate(htonl(cmd->uid)))
        return false;
    NetworkAddLANCandidate();
    return true;
}
#else
static bool NetworkTryAddLANCandidate(struct network_packet* packet) {
    CmdPacket_s* cmd = (CmdPacket_s*)packet->buffer;
    if(NetworkCheckDuplicateLANCandidate(htonl(cmd->uid)))
        return false;
    NetworkAddLANCandidate(packet);
    return true;
}
#endif

#if USE_SDLNET
static void NetworkStageLANCandidate(void) {
    LANClient* lan = gLANClientCandidates + 0;
    lan->address = packet->address.host;
    printf("Received packet from %d.%d.%d.%d\n", 
        lan->address & 0xff, 
        (lan->address >> 8) & 0xff,
        (lan->address >> 16) & 0xff,
        (lan->address >> 24) & 0xff);
    memset(lan->name, 0x50, sizeof(lan->name));
    CmdPacket_s* cmd = (CmdPacket_s*)packet->data;
    lan->uid = htonl(cmd->uid);
    memcpy(lan->name, cmd->host_lan.name, 10);
    lan->trainerId = htons(cmd->host_lan.trainerId);
    lan->gender = cmd->host_lan.gender;
}
#else
static void NetworkStageLANCandidate(struct network_packet* packet) {
    LANClient* lan = gLANClientCandidates + 0;
    lan->address = packet->sender._addr4.host[0] | 
        (packet->sender._addr4.host[1] << 8) |
        (packet->sender._addr4.host[2] << 16) |
        (packet->sender._addr4.host[3] << 24);
    printf("Received packet from %d.%d.%d.%d\n", 
        lan->address & 0xff, 
        (lan->address >> 8) & 0xff,
        (lan->address >> 16) & 0xff,
        (lan->address >> 24) & 0xff);
    memset(lan->name, 0x50, sizeof(lan->name));
    CmdPacket_s* cmd = (CmdPacket_s*)packet->buffer;
    lan->uid = htonl(cmd->uid);
    memcpy(lan->name, cmd->host_lan.name, 10);
    lan->trainerId = htons(cmd->host_lan.trainerId);
    lan->gender = cmd->host_lan.gender;
}
#endif

bool NetworkCheckLAN(void) {
#if USE_SDLNET
    if(NetworkTryRecvUDP() && gLANClientCandidateCount < 16) {
        if(packet->len < UDP_PACKET_SIZE - 16 || packet->len > UDP_PACKET_SIZE + 16) {
            printf("Packet length was not in expected range (%d-%d): %d\n", UDP_PACKET_SIZE - 16, UDP_PACKET_SIZE + 16, packet->len);
            return false;
        }

        CmdPacket_s* cmd = (CmdPacket_s*)packet->data;
        printf("UDP Packet: %d.%d.%d.%d\n", packet->address.host & 0xff,
            (packet->address.host >> 8) & 0xff,
            (packet->address.host >> 16) & 0xff,
            (packet->address.host >> 24) & 0xff);

        // Did we send the packet? If so, ignore it.
        if(cmd->uid == htonl(hostUniqueId))
            return false;

        switch(cmd->type) {
            case CMD_HOST_LAN:
                if(gNetworkState == NETSTATE_JOINING) {
                    return NetworkTryAddLANCandidate();
                }
                return false;
            case CMD_JOIN_LAN:
                if(gNetworkState == NETSTATE_HOSTING) {
                    NetworkStageLANCandidate();
                    return true;
                }
                return false;
            case CMD_ACCEPT_JOIN_LAN:
                if(gNetworkState == NETSTATE_JOINING) {
                    return NetworkAcceptLANConnection();
                }
                return false;
        }
    }
    return false;
#else
    struct network_data* state = &gNetworkData;
    if(recv_packet(state->udp, &state->udp_packet) > 0 && gLANClientCandidateCount < 16) {
        struct network_packet* packet = &state->udp_packet;

        if(packet->len < UDP_PACKET_SIZE - 16 || packet->len > UDP_PACKET_SIZE + 16) {
            printf("Packet length was not in expected range (%d-%d): %d\n", UDP_PACKET_SIZE - 16, UDP_PACKET_SIZE + 16, packet->len);
            return false;
        }

        CmdPacket_s* cmd = (CmdPacket_s*)packet->buffer;
        printf("UDP Packet: %d.%d.%d.%d\n", 
            packet->sender._addr4.host[0],
            packet->sender._addr4.host[1],
            packet->sender._addr4.host[2],
            packet->sender._addr4.host[3]);

        // Did we send the packet? If so, ignore it.
        if(cmd->uid == htonl(hostUniqueId))
            return false;

        switch(cmd->type) {
            case CMD_HOST_LAN:
                if(gNetworkState == NETSTATE_JOINING) {
                    return NetworkTryAddLANCandidate(packet);
                }
                return false;
            case CMD_JOIN_LAN:
                if(gNetworkState == NETSTATE_HOSTING) {
                    NetworkStageLANCandidate(packet);
                    return true;
                }
                return false;
            case CMD_ACCEPT_JOIN_LAN:
                if(gNetworkState == NETSTATE_JOINING) {
                    return NetworkAcceptLANConnection();
                }
                return false;
        }
    }
    return false;
#endif
}

void NetworkClearLANCache(void) {
    gLANClientCandidateCount = 0;
    memset(gLANClientCandidates, 0, sizeof(gLANClientCandidates));
#if USE_SDLNET
    NetworkTossQueueingPackets();
#else
    NetworkTossQueueingPackets(&gNetworkData);
#endif
}

LANClient* NetworkGetLANCandidate(uint32_t which) {
    return gLANClientCandidates + which;
}

uint32_t NetworkGetLANCandidateCount(void) {
    return gLANClientCandidateCount;
}

#if USE_SDLNET
static void NetworkSetLinkSocket(TCPsocket socket) {
    if(linkSocket != NULL) {
        SDLNet_TCP_DelSocket(sockets, linkSocket);
    }
    linkSocket = socket;
    SDLNet_TCP_AddSocket(sockets, linkSocket);
}
#endif

bool NetworkLANDirectConnect(uint32_t which) {
#if USE_SDLNET
    serial = SDLNet_TCP_Open(&(IPaddress){.host = INADDR_ANY, .port = htons(TCP_PORT)});
    packet->address.host = gLANClientCandidates[which].address;
    CmdPacket_s* cmd = (CmdPacket_s*)packet->data;
    cmd->type = CMD_ACCEPT_JOIN_LAN;
    cmd->uid = htonl(hostUniqueId);
    SDLNet_UDP_Send(host, -1, packet);
    uint32_t timeout = 60 * 8;
    while(!(cserial = SDLNet_TCP_Accept(serial))) {
        DelayFrame();
        if(--timeout == 0) {
            printf("Connection timed out...\n");
            SDLNet_TCP_Close(serial);
            serial = NULL;
            return false;
        }
    }
    printf("Hosting %d.%d.%d.%d!\n", 
        packet->address.host & 0xff, 
        (packet->address.host >> 8) & 0xff,
        (packet->address.host >> 16) & 0xff,
        (packet->address.host >> 24) & 0xff);
    NetworkSetLinkSocket(cserial);
    gNetworkState = NETSTATE_LAN_HOST;
    gb.gb_serial_rx = gb_serial_rx;
    gb.gb_serial_tx = gb_serial_tx;
    return true;
#else
    struct network_data* state = &gNetworkData;
    struct network_packet* packet = &gNetworkData.udp_packet;
    state->serial = socket_open(MOBILE_SOCKTYPE_TCP, MOBILE_ADDRTYPE_IPV4, TCP_PORT);
    if(state->serial != INVALID_SOCKET) {
        if(socket_listen(state->serial)) {
            memcpy(packet->sender._addr4.host, &gLANClientCandidates[which].address, 4);
            CmdPacket_s* cmd = (CmdPacket_s*)packet->buffer;
            cmd->type = CMD_ACCEPT_JOIN_LAN;
            cmd->uid = htonl(hostUniqueId);
            socket_send(state->udp, packet->buffer, packet->len, &packet->sender);
            uint32_t timeout = 60 * 8;
            SOCKET cserial = INVALID_SOCKET;
            while((cserial = socket_accept(state->serial), cserial == INVALID_SOCKET)) {
                DelayFrame();
                if(--timeout == 0) {
                    printf("Connection timed out...\n");
                    socket_close(state->serial);
                    state->serial = INVALID_SOCKET;
                    return false;
                }
            }
            state->serial = cserial;
            state->linkSocket = state->serial;
            printf("Hosting %d.%d.%d.%d!\n", 
                packet->sender._addr4.host[0], 
                packet->sender._addr4.host[1], 
                packet->sender._addr4.host[2], 
                packet->sender._addr4.host[3]);
            memcpy(&state->linkAddr, &packet->sender, sizeof(state->linkAddr));
            gNetworkState = NETSTATE_LAN_HOST;
            gb.gb_serial_rx = gb_serial_rx;
            gb.gb_serial_tx = gb_serial_tx;
            return true;
        }
        else {
            socket_close(state->serial);
            state->serial = INVALID_SOCKET;
        }
    }
    return false;
#endif
}

bool NetworkAcceptLANConnection(void) {
#if USE_SDLNET
    serial = SDLNet_TCP_Open(&(IPaddress){.host = packet->address.host, .port = htons(TCP_PORT)});
    if(serial != NULL) {
        NetworkSetLinkSocket(serial);
        gNetworkState = NETSTATE_LAN_CLIENT;
        printf("Connected to %d.%d.%d.%d!\n",
            packet->address.host & 0xff, 
            (packet->address.host >> 8) & 0xff,
            (packet->address.host >> 16) & 0xff,
            (packet->address.host >> 24) & 0xff);
        gb.gb_serial_rx = gb_serial_rx;
        gb.gb_serial_tx = gb_serial_tx;
        return true;
    }
    printf("SDLNet: Error trying to connect to %d.%d.%d.%d\n %s\n",
        packet->address.host & 0xff, 
        (packet->address.host >> 8) & 0xff,
        (packet->address.host >> 16) & 0xff,
        (packet->address.host >> 24) & 0xff,
        SDLNet_GetError());
    return false;
#else
    struct network_data* state = &gNetworkData;
    struct network_packet* packet = &gNetworkData.udp_packet;
    state->serial = socket_open(MOBILE_SOCKTYPE_TCP, MOBILE_ADDRTYPE_IPV4, TCP_PORT);
    if(state->serial != INVALID_SOCKET) {
        int err = socket_connect_ip(state->serial, &packet->sender);
        if(err > 0) {
            state->linkSocket = state->serial;
            gNetworkState = NETSTATE_LAN_CLIENT;
            printf("Connected to %d.%d.%d.%d!\n",
                packet->sender._addr4.host[0], 
                packet->sender._addr4.host[1], 
                packet->sender._addr4.host[2], 
                packet->sender._addr4.host[3]);
            memcpy(&state->linkAddr, &packet->sender, sizeof(state->linkAddr));
            gb.gb_serial_rx = gb_serial_rx;
            gb.gb_serial_tx = gb_serial_tx;
            return true;
        }
        else {
            socket_close(state->serial);
            state->serial = INVALID_SOCKET;
        }
    }
    printf("Error trying to connect to %d.%d.%d.%d\n",
        packet->sender._addr4.host[0], 
        packet->sender._addr4.host[1], 
        packet->sender._addr4.host[2], 
        packet->sender._addr4.host[3]);
    return false;
#endif
}

void NetworkCloseConnection(void) {
#if USE_SDLNET
    if(linkSocket) {
        SDLNet_TCP_DelSocket(sockets, linkSocket);
        linkSocket = NULL;
    }
    if(cserial) {
        SDLNet_TCP_Close(cserial);
        cserial = NULL;
    }
    if(serial) {
        SDLNet_TCP_Close(serial);
        serial = NULL;
    }
#else
    struct network_data* state = &gNetworkData;
    state->linkSocket = INVALID_SOCKET;
    if(state->serial != INVALID_SOCKET) {
        socket_close(state->serial);
        state->serial = INVALID_SOCKET;
    }
#endif
    gb.gb_serial_rx = gb_serial_rx_test;
    gb.gb_serial_tx = gb_serial_tx_test;
    gNetworkState = NETSTATE_NOTHING;
}

#if !USE_SDLNET
void NetworkQuit(void) {
    #if defined(_WIN32)
    /* Clean up windows networking */
    if ( WSACleanup() == SOCKET_ERROR ) {
        if ( WSAGetLastError() == WSAEINPROGRESS ) {
            WSACleanup();
        }
    }
    #else
    /* Restore the SIGPIPE handler */
    void (*handler)(int);
    handler = signal(SIGPIPE, SIG_DFL);
    if ( handler != SIG_IGN ) {
        signal(SIGPIPE, handler);
    }
    #endif
}
#endif

void NetworkDeinit(void) {
#if USE_SDLNET
    if(gNetworkingInit) {
        if(packet != NULL) {
            SDLNet_FreePacket(packet);
        }
        if(host != NULL) {
            SDLNet_UDP_Close(host);
        }
        SDLNet_Quit();
        gNetworkingInit = false;
    }
#else
    struct network_data* state = &gNetworkData;
    if(gNetworkingInit) {
        if(state->udp_packet.buffer != NULL) {
            free(state->udp_packet.buffer);
            state->udp_packet.buffer = NULL;
        }
        memset(&state->udp_packet, 0, sizeof(state->udp_packet));
        if(state->udp != INVALID_SOCKET) {
            socket_close(state->udp);
            state->udp = INVALID_SOCKET;
        }
        NetworkQuit();
        gNetworkingInit = false;
    }
#endif
}

#define MAX_EXCHANGE_BYTE_TRIES 60

int Network_ExchangeByte(uint8_t* rx, uint8_t tx) {
#if USE_SDLNET
    switch(gNetworkState) {
    case NETSTATE_LAN_HOST: {
        if(SDLNet_TCP_Send(linkSocket, &tx, sizeof(tx)) <= 0)
            return NETWORK_XCHG_ERROR_SEND;

        uint32_t tries = 0;
        while(tries < MAX_EXCHANGE_BYTE_TRIES) {
            if(SDLNet_CheckSockets(sockets, 0) != 0) {
                if(SDLNet_TCP_Recv(linkSocket, rx, sizeof(*rx)) <= 0)
                    return NETWORK_XCHG_ERROR_RECV;
                return NETWORK_XCHG_OK;
            }
            DelayFrame();
            tries++;
        }

        return NETWORK_XCHG_TIMEOUT;
    } break;
    case NETSTATE_LAN_CLIENT: {
        uint32_t tries = 0;
        while(tries < MAX_EXCHANGE_BYTE_TRIES) {
            if(SDLNet_CheckSockets(sockets, 0) != 0) {
                if(SDLNet_TCP_Recv(linkSocket, rx, sizeof(*rx)) <= 0) {
                    return NETWORK_XCHG_ERROR_RECV;
                }
                if(SDLNet_TCP_Send(linkSocket, &tx, sizeof(tx)) <= 0) {
                    return NETWORK_XCHG_ERROR_SEND;
                }
                return NETWORK_XCHG_OK;
            }
            DelayFrame();
            tries++;
        }

        return NETWORK_XCHG_TIMEOUT;
    } break;
    default:
        return NETWORK_XCHG_NO_CONNECTION;
    }
#else
    struct network_data* state = &gNetworkData;
    switch(gNetworkState) {
    case NETSTATE_LAN_HOST: {
        if(socket_send(state->linkSocket, &tx, sizeof(tx), &state->linkAddr) <= 0)
            return NETWORK_XCHG_ERROR_SEND;

        uint32_t tries = 0;
        while(tries < MAX_EXCHANGE_BYTE_TRIES) {
            if(socket_hasdata(state->linkSocket) > 0) {
                if(socket_recv(state->linkSocket, rx, sizeof(*rx), &state->linkAddr) <= 0)
                    return NETWORK_XCHG_ERROR_RECV;
                return NETWORK_XCHG_OK;
            }
            DelayFrame();
            tries++;
        }

        return NETWORK_XCHG_TIMEOUT;
    } break;
    case NETSTATE_LAN_CLIENT: {
        uint32_t tries = 0;
        while(tries < MAX_EXCHANGE_BYTE_TRIES) {
            if(socket_hasdata(state->linkSocket) > 0) {
                if(socket_recv(state->linkSocket, rx, sizeof(*rx), &state->linkAddr) <= 0) {
                    return NETWORK_XCHG_ERROR_RECV;
                }
                if(socket_send(state->linkSocket, &tx, sizeof(tx), &state->linkAddr) <= 0) {
                    return NETWORK_XCHG_ERROR_SEND;
                }
                return NETWORK_XCHG_OK;
            }
            DelayFrame();
            tries++;
        }

        return NETWORK_XCHG_TIMEOUT;
    } break;
    default:
        return NETWORK_XCHG_NO_CONNECTION;
    }
#endif
}

bool Network_SafeExchangeByte(uint8_t* rx, uint8_t tx) {
    int timeout_count = 0;
    int error;
#if USE_SDLNET
    if(serial == NULL && cserial == NULL)
        goto no_connection;
#else
    if(gNetworkData.linkSocket == INVALID_SOCKET)
        goto no_connection;
#endif
try_again:
    error = Network_ExchangeByte(rx, tx);
    switch(error) {
    case NETWORK_XCHG_OK:
        return true;
    case NETWORK_XCHG_ERROR_RECV:
    case NETWORK_XCHG_ERROR_SEND:
        #if USE_SDLNET
        printf("SDLNet error: %s\n", SDLNet_GetError());
        #endif
        return false;
    case NETWORK_XCHG_TIMEOUT:
        printf("Timeout, trying again...\n");
        timeout_count++;
        if(timeout_count > 8)
            return false;
        goto try_again;
    case NETWORK_XCHG_NO_CONNECTION:
    no_connection:
        printf("No connection established...\n");
        return false;
    }
    return false;
}

int Network_ExchangeBytes(void* rx, const void* tx, int len) {
#if USE_SDLNET
    switch(gNetworkState) {
    case NETSTATE_LAN_HOST: {
        if(SDLNet_TCP_Send(linkSocket, tx, len) < len)
            return NETWORK_XCHG_ERROR_SEND;

        uint32_t tries = 0;
        while(tries < MAX_EXCHANGE_BYTE_TRIES) {
            int ready = SDLNet_CheckSockets(sockets, 0);
            if(ready < 0) {
                return NETWORK_XCHG_ERROR_RECV;
            }
            else if(ready > 0) {
                if(SDLNet_TCP_Recv(linkSocket, rx, len) <= 0)
                    return NETWORK_XCHG_ERROR_RECV;
                return NETWORK_XCHG_OK;
            }
            DelayFrame();
            tries++;
        }

        return NETWORK_XCHG_TIMEOUT;
    } break;
    case NETSTATE_LAN_CLIENT: {
        uint32_t tries = 0;
        while(tries < MAX_EXCHANGE_BYTE_TRIES) {
            int ready = SDLNet_CheckSockets(sockets, 0);
            if(ready < 0) {
                return NETWORK_XCHG_ERROR_RECV;
            }
            else if(ready > 0) {
                if(SDLNet_TCP_Recv(linkSocket, rx, len) <= 0) {
                    return NETWORK_XCHG_ERROR_RECV;
                }
                if(SDLNet_TCP_Send(linkSocket, tx, len) < len) {
                    return NETWORK_XCHG_ERROR_SEND;
                }
                return NETWORK_XCHG_OK;
            }
            DelayFrame();
            tries++;
        }

        return NETWORK_XCHG_TIMEOUT;
    } break;
    default:
        return NETWORK_XCHG_NO_CONNECTION;
    }
#else
    struct network_data* state = &gNetworkData;
    switch(gNetworkState) {
    case NETSTATE_LAN_HOST: {
        if(socket_send(state->linkSocket, tx, len, &state->linkAddr) < len)
            return NETWORK_XCHG_ERROR_SEND;

        uint32_t tries = 0;
        while(tries < MAX_EXCHANGE_BYTE_TRIES) {
            int ready = socket_hasdata(state->linkSocket);
            if(ready < 0) {
                return NETWORK_XCHG_ERROR_RECV;
            }
            else if(ready > 0) {
                if(socket_recv(state->linkSocket, rx, len, &state->linkAddr) <= 0)
                    return NETWORK_XCHG_ERROR_RECV;
                return NETWORK_XCHG_OK;
            }
            DelayFrame();
            tries++;
        }

        return NETWORK_XCHG_TIMEOUT;
    } break;
    case NETSTATE_LAN_CLIENT: {
        uint32_t tries = 0;
        while(tries < MAX_EXCHANGE_BYTE_TRIES) {
            int ready = socket_hasdata(state->linkSocket);
            if(ready < 0) {
                return NETWORK_XCHG_ERROR_RECV;
            }
            else if(ready > 0) {
                if(socket_recv(state->linkSocket, rx, len, &state->linkAddr) <= 0) {
                    return NETWORK_XCHG_ERROR_RECV;
                }
                if(socket_send(state->linkSocket, tx, len, &state->linkAddr) < len) {
                    return NETWORK_XCHG_ERROR_SEND;
                }
                return NETWORK_XCHG_OK;
            }
            DelayFrame();
            tries++;
        }

        return NETWORK_XCHG_TIMEOUT;
    } break;
    default:
        return NETWORK_XCHG_NO_CONNECTION;
    }
#endif
}

bool Network_SafeExchangeBytes(void *rx, const void *tx, int len)
{
    int timeout_count = 0;
    int error;
#if USE_SDLNET
    if(linkSocket == NULL)
        goto no_connection;
#else
    if(gNetworkData.linkSocket == INVALID_SOCKET)
        goto no_connection;
#endif
try_again:
    error = Network_ExchangeBytes(rx, tx, len);
    switch(error) {
    case NETWORK_XCHG_OK:
        printf("Send:");
        for(int i = 0; i < len; ++i) {
            printf(" $%02X", ((uint8_t*)tx)[i]);
        }
        printf(".\n");
        printf("Recv:");
        for(int i = 0; i < len; ++i) {
            printf(" $%02X", ((uint8_t*)rx)[i]);
        }
        printf(".\n");
        return true;
    case NETWORK_XCHG_ERROR_RECV:
    case NETWORK_XCHG_ERROR_SEND:
        #if USE_SDLNET
        printf("SDLNet error: %s\n", SDLNet_GetError());
        #endif
        return false;
    case NETWORK_XCHG_TIMEOUT:
        printf("Timeout, trying again...\n");
        timeout_count++;
        if(timeout_count > 8)
            return false;
        goto try_again;
    case NETWORK_XCHG_NO_CONNECTION:
    no_connection:
        printf("No connection established...\n");
        return false;
    }
    return false;
}

void Network_FlushPendingPacketsAndSync(void) {
#if USE_SDLNET
    uint8_t sink;
    while(SDLNet_CheckSockets(sockets, 0) > 0 && SDLNet_TCP_Recv(linkSocket, &sink, 1) > 0) {}
#else
    struct network_data* state = &gNetworkData;
    uint8_t sink;
    while(socket_hasdata(state->linkSocket) > 0 && socket_recv(state->linkSocket, &sink, 1, &state->linkAddr) > 0) {}
#endif
}

int Network_SendByte(uint8_t byte) {
#if USE_SDLNET
    if(linkSocket == NULL)
        return NETWORK_XCHG_NO_CONNECTION;
    if(SDLNet_TCP_Send(linkSocket, &byte, 1) <= 0)
        return NETWORK_XCHG_ERROR_SEND;
#else
    struct network_data* state = &gNetworkData;
    if(state->linkSocket == INVALID_SOCKET)
        return NETWORK_XCHG_NO_CONNECTION;
    if(socket_send(state->linkSocket, &byte, 1, &state->linkAddr) <= 0)
        return NETWORK_XCHG_ERROR_SEND;
#endif
#if DEBUG
    printf("Send $%02x (%d)\n", byte, byte);
#endif
    return NETWORK_XCHG_OK;
}

int Network_TryRecvByte(uint8_t* dest) {
#if USE_SDLNET
    int ready = SDLNet_CheckSockets(sockets, 0);
    if(ready < 0)
        return NETWORK_XCHG_ERROR_RECV;
    else if(ready == 0)
        return NETWORK_XCHG_TIMEOUT;
    else {
        int error = SDLNet_TCP_Recv(linkSocket, dest, 1);
        if(error <= 0)
            return NETWORK_XCHG_ERROR_RECV;
#if DEBUG
        printf("Recv $%02x (%d)\n", *dest, *dest);
#endif
        return NETWORK_XCHG_OK;
    }
#else
    struct network_data* state = &gNetworkData;
    int ready = socket_hasdata(state->linkSocket);
    if(ready < 0)
        return NETWORK_XCHG_ERROR_RECV;
    else if(ready == 0)
        return NETWORK_XCHG_TIMEOUT;
    else {
        int error = socket_recv(state->linkSocket, dest, 1, &state->linkAddr);
        if(error <= 0)
            return NETWORK_XCHG_ERROR_RECV;
        return NETWORK_XCHG_OK;
    }
#endif
}

bool Network_SafeTryRecvByte(uint8_t* dest) {
    int error = Network_TryRecvByte(dest);
    switch(error) {
    case NETWORK_XCHG_OK:
        return true;
    default:
    case NETWORK_XCHG_ERROR_RECV:
        #if USE_SDLNET
        printf("Error: %s\n", SDLNet_GetError());
        #endif
        return false;
    case NETWORK_XCHG_TIMEOUT:
        return false;
    }
}

bool Network_ResolveHost(const char* hostname, const char* port, struct mobile_addr* addr) {
    union u_sockaddr u_addr;
    if(!resolve_host(hostname, port, &u_addr.addr)) {
        printf("%s:%s => Error\n",
            hostname, port);
        return false;
    }
    addr->type = MOBILE_ADDRTYPE_IPV4;
    struct mobile_addr4* addr4 = (struct mobile_addr4*)addr;
    addr4->port = ntohs(u_addr.addr4.sin_port);
    memcpy(addr4->host, &u_addr.addr4.sin_addr.s_addr, sizeof(addr4->host));
    printf("%s:%s => %d.%d.%d.%d:%d\n",
        hostname, port,
        addr4->host[0], addr4->host[1],
        addr4->host[2], addr4->host[3],
        addr4->port);
    return true;
}

void Network_ResolveHostToIPString(char* dest, const char* hostname, const char* port) {
    struct mobile_addr a;
    if(Network_ResolveHost(hostname, port, &a)) {
        struct mobile_addr4* addr4 = (struct mobile_addr4*)&a;
        snprintf(dest, 16, "%d.%d.%d.%d",
            addr4->host[0], addr4->host[1],
            addr4->host[2], addr4->host[3]);
        return;
    }
}

/// Mobile interface

enum {
    MOBILE_USER_ENABLED_F,
    MOBILE_USER_32BIT_F,
};
#define MOBILE_USER_ENABLED (1 << MOBILE_USER_ENABLED_F)
#define MOBILE_USER_32BIT   (1 << MOBILE_USER_32BIT_F)

struct mobile_user_data {
    uint32_t flags;
    SOCKET sockets[MOBILE_MAX_CONNECTIONS];
    const char* logpath;
    uint32_t timers[MOBILE_MAX_TIMERS];
    uint8_t config[MOBILE_CONFIG_SIZE];
};
static struct mobile_adapter* gMobileAdapter;
static struct mobile_user_data gMobileData;
static uint8_t gMobileByte;
static uint8_t gMobileByteLast;

bool MobileCheckSerialEnabled(void);

static void gb_serial_tx_test(const uint8_t x) {
    if(MobileCheckSerialEnabled()) {
        gMobileByte = gMobileByteLast;
        gMobileByteLast = MobileTransfer(x);
        // FILE* f = fopen("mobile_packets.log", "a");
        // fprintf(f, "A %02X %02X\n", gMobileByte, x);
        // fclose(f);
        if(gMobileByte == 0xD2 && x == 0x4B)
            return;
    #if DEBUG
        // printf("A %02X %02X\n", gMobileByte, x);
    #endif
    }
}

static enum gb_serial_rx_ret_e gb_serial_rx_test(uint8_t* x) {
    // receive byte
    if(MobileCheckSerialEnabled()) {
        // printf("serial recv: %02x (%d)\n", gMobileByteLast, gMobileByteLast);
        *x = gMobileByte;
        return GB_SERIAL_RX_SUCCESS;
    }
    *x = 0xff;
    return GB_SERIAL_RX_NO_CONNECTION;
}

void MobileDebugLog(void* user, const char* line) {
    struct mobile_user_data* udata = user;
    if(udata->logpath) {
        FILE* f = fopen(udata->logpath, "ab");
        fprintf(f, "%s\n", line);
        fclose(f);
    }
    else {
    #if DEBUG
        printf("mobile: %s\n", line);
    #endif
    }
}

void socket_impl_init(struct mobile_user_data *state)
{
    for (unsigned i = 0; i < MOBILE_MAX_CONNECTIONS; i++) {
        state->sockets[i] = INVALID_SOCKET;
    }
}

void socket_impl_stop(struct mobile_user_data *state)
{
    for (unsigned i = 0; i < MOBILE_MAX_CONNECTIONS; i++) {
        if (state->sockets[i] != INVALID_SOCKET) {
            socket_close(state->sockets[i]);
        }
    }
}

bool socket_impl_open(void *data, unsigned conn, enum mobile_socktype type, enum mobile_addrtype addrtype, unsigned bindport)
{
    struct mobile_user_data *state = data;
    assert(state->sockets[conn] == INVALID_SOCKET);

    SOCKET sock = socket_open(type, addrtype, bindport);
    if(sock == INVALID_SOCKET)
        return false;

    state->sockets[conn] = sock;
    return true;
}

void socket_impl_close(void *data, unsigned conn)
{
    struct mobile_user_data *state = data;
    assert(state->sockets[conn] != INVALID_SOCKET);
    socket_close(state->sockets[conn]);
    state->sockets[conn] = INVALID_SOCKET;
}

int socket_impl_connect(void *data, unsigned conn, const struct mobile_addr *addr)
{
    struct mobile_user_data *state = data;
    SOCKET sock = state->sockets[conn];

    return socket_connect_ip(sock, addr);
}

bool socket_impl_listen(void *data, unsigned conn)
{
    struct mobile_user_data *state = data;
    SOCKET sock = state->sockets[conn];
    assert(sock != INVALID_SOCKET);

    if (listen(sock, 1) == SOCKET_ERROR) {
        socket_perror("listen");
        return false;
    }

    return true;
}

bool socket_impl_accept(void *data, unsigned conn)
{
    struct mobile_user_data *state = data;
    SOCKET sock = state->sockets[conn];

    SOCKET newsock = socket_accept(sock);
    if(newsock == INVALID_SOCKET)
        return false;
    state->sockets[conn] = newsock;
    return true;
}

int socket_impl_send(void *udata, unsigned conn, const void *data, const unsigned size, const struct mobile_addr *addr)
{
    struct mobile_user_data *state = udata;
    SOCKET sock = state->sockets[conn];

    return socket_send(sock, data, size, addr);
}

int socket_impl_recv(void *udata, unsigned conn, void *data, unsigned size, struct mobile_addr *addr)
{
    struct mobile_user_data *state = udata;
    SOCKET sock = state->sockets[conn];

    return socket_recv(sock, data, size, addr);
}

// mobile_func_serial_enable - Enable serial communications
//
// Exact opposite of mobile_func_serial_disable(). This function indicates
// mobile_transfer() may be called again, resuming communications.
//
// The <mode_32bit> parameter indicates in which mode the serial peripheral
// should be initialized. It indicates whether each serial transmission by the
// console will contain 8 or 32 bits. When <mode_32bit> is ON, the
// mobile_transfer_32bit() function must be used instead of mobile_transfer().
// This information is also relevant for hardware implementations, which must
// configure their hardware to receive bursts of 32 bits of data.
void MobileSerialEnable(void* user, bool mode_32bit) {
    struct mobile_user_data* udata = user;
    udata->flags |= MOBILE_USER_ENABLED | ((mode_32bit)? MOBILE_USER_32BIT: 0);
}

// mobile_func_serial_disable - Disable serial communications
//
// This function must ensure nothing will call mobile_transfer() while the
// serial communcations are disabled, and the current byte transfer state is
// reset, in case a byte was partially transferred at the time this function
// was called. If mobile_transfer() and mobile_loop() are implemented as
// separate threads, a mutex-like locking mechanism may be used to accomplish
// this.
void MobileSerialDisable(void* user) {
    struct mobile_user_data* udata = user;
    udata->flags &= ~(MOBILE_USER_ENABLED | MOBILE_USER_32BIT);
}

// mobile_func_time_latch - Latch a timer
//
// Timers are used to keep track of time, allowing libmobile to implement
// timeouts and other time-related mechanisms. The time tracked must reflect
// the same measurement the connected gameboy is using. This means that when an
// emulated gameboy is sped up, the timer will move faster as well. If
// connected to a real-life gameboy, this will track real time. An
// implementation must be able to track MOBILE_MAX_TIMERS amount of timers, and
// all timers must be treated exactly the same. Timers must be able to keep
// track of at least 60 seconds, with millisecond precision, preferably with
// little to no time skew.
//
// This function will "latch" the current time to the specified timer, by
// storing the current value so it may later be compared.
//
// Parameters:
// - timer: timer that should be latched
void MobileTimeLatch(void* user, unsigned int timer) {
    struct mobile_user_data* udata = user;
    udata->timers[timer] = SDL_GetTicks();
}

// mobile_func_time_check_ms - Check if a certain amount of time has passed
//
// Checks if a specified amount of milliseconds has passed since a timer has
// been latched by mobile_func_time_latch(). The notes on that function apply
// here as well.
//
// Checking a timer that hasn't been latched is undefined, libmobile shall never
// do this.
//
// Returns: true if the specified time has passed, false otherwise
// Parameters:
// - timer: timer that should be compared against
// - ms: amount of milliseconds that should be compared with
bool MobileTimeCheckMs(void* user, unsigned int timer, unsigned int ms) {
    struct mobile_user_data* udata = user;
    return (SDL_GetTicks() - udata->timers[timer]) >= ms;
}

struct mobile_config {
    char hdr[2];
    uint8_t status;
    uint8_t fld_03;
    uint8_t primary_dns[4];
    uint8_t secondary_dns[4];
    char loginName[10];
    uint8_t fld_16[0x2C - 0x16];
    char emailName[0x44 - 0x2C];
    uint8_t fld_45[0x4A - 0x44];
    char smtpServer[0x5E - 0x4A];
    char popServer[0x71 - 0x5E];
    uint8_t fld_71[0x76 - 0x71];
    struct config_slot {
        uint8_t number[8];
        char id[16]; 
    } config_slot[3];
};

struct server_config {
    char hostname[64];
    char loginPass[20];
    char relayServer[64];
};

static struct server_config gServerConfig;

enum {
    MOBILE_CONFIG_STATUS_NONE,
    MOBILE_CONFIG_STATUS_CONFIGURING = 0x1,
    MOBILE_CONFIG_STATUS_CONFIGURED = 0x81,
};

void MobileNumberStore(uint8_t* dst, size_t size, const char* src) {
    size_t max_digits = size * 2;
    uint8_t nextNum = 0;
    size_t i = 0;
    while(i < max_digits) {
        char c = src[i];
        uint8_t val = 0;
        if(c >= '0' && c <= '9') {
            val = c - '0';
        }
        else if(c == '#') {
            val = 0xA;
        }
        else if(c == '*') {
            val = 0xB;
        }
        else if(c == '\0') {
            val = 0xF;
        }
        if((i & 1) == 1) {
            nextNum |= val & 0xf;
            dst[i / 2] = nextNum;
        } else {
            nextNum = (val << 4);
            dst[i / 2] = nextNum;
        }
        i++;
        if(c == '\0') {
            return;
        }
    }
}

// Additional server override values are stored in server.json.
// These values will override existing default values for the server
// hostname, and login password as well as some values from the mobile
// config loaded from mobile.bin.
void LoadMobileServerConfig(struct server_config* srv, struct mobile_config* cfg) {
    asset_s a = LoadTextAsset("server.json");
    if(a.ptr == NULL)
        return;

    json_value_t* root = json_parse(a.ptr, a.size);
    if(!root) {
        FreeAsset(a);
        return;
    }

    json_object_t* root_object = json_value_as_object(root);
    if(!root_object)
        goto end;

    for(json_object_element_t* it = root_object->start; it != NULL; it = it->next) {
        if(strcmp(it->name->string, "hostname") == 0) {
            json_string_t *s = json_value_as_string(it->value);
            if(s == NULL)
                continue;

            if(s->string_size == 0)
                continue;
            
            memset(srv->hostname, 0, sizeof(srv->hostname));
            strncpy(srv->hostname, s->string, sizeof(srv->hostname) - 1);
        }
        if(strcmp(it->name->string, "pop_host") == 0) {
            json_string_t *s = json_value_as_string(it->value);
            if(s == NULL)
                continue;

            if(s->string_size == 0 || s->string_size > sizeof(cfg->popServer))
                continue;
            
            memset(cfg->popServer, 0, sizeof(cfg->popServer));
            memcpy(cfg->popServer, s->string, sizeof(cfg->popServer));
        }
        if(strcmp(it->name->string, "mail_host") == 0) {
            json_string_t *s = json_value_as_string(it->value);
            if(s == NULL)
                continue;

            if(s->string_size == 0 || s->string_size > sizeof(cfg->smtpServer))
                continue;
            
            memset(cfg->smtpServer, 0, sizeof(cfg->smtpServer));
            memcpy(cfg->smtpServer, s->string, sizeof(cfg->smtpServer));
        }
        else if(strcmp(it->name->string, "login_name") == 0) {
            json_string_t *s = json_value_as_string(it->value);
            if(s == NULL)
                continue;

            if(s->string_size == 0)
                continue;

            if(s->string_size != sizeof(cfg->loginName)) {
                fprintf(stderr, "For field %s, Bad string size: %llu\n", it->name->string, (unsigned long long)s->string_size);
                continue;
            }
            
            memcpy(cfg->loginName, s->string, sizeof(cfg->loginName));
        }
        else if(strcmp(it->name->string, "email_id") == 0) {
            json_string_t *s = json_value_as_string(it->value);
            if(s == NULL)
                continue;

            if(s->string_size == 0)
                continue;

            if(s->string_size != 8) {
                fprintf(stderr, "For field %s, Bad string size: %llu\n", it->name->string, (unsigned long long)s->string_size);
                continue;
            }
            
            memcpy(cfg->emailName, s->string, 8);
        }
        else if(strcmp(it->name->string, "login_pass") == 0) {
            json_string_t *s = json_value_as_string(it->value);
            if(s == NULL)
                continue;

            if(s->string_size == 0)
                continue;
            
            memset(srv->loginPass, 0, sizeof(srv->loginPass));
            strncpy(srv->loginPass, s->string, sizeof(srv->loginPass) - 1);
        }
    }

end:
    free(root);
    FreeAsset(a);
    return;
}

const char* Mobile_GetServerHostname(void) {
    return gServerConfig.hostname;
}

const char* Mobile_GetServerLoginPassword(uint8_t maxLength) {
    int len = strlen(gServerConfig.loginPass);
    if(len == 0 || len > maxLength)
        return NULL;
    return gServerConfig.loginPass;
}

void MobileConfigCreateDefault(FILE* f) {
    uint8_t buffer[MOBILE_CONFIG_SIZE];
    memset(buffer, 0x0, sizeof(buffer));
    struct mobile_config* cfg = (struct mobile_config*)buffer;
    cfg->hdr[0] = 'M';
    cfg->hdr[1] = 'A';
    cfg->status = MOBILE_CONFIG_STATUS_CONFIGURED;
    memcpy(cfg->loginName, "g000000000", sizeof(cfg->loginName));
    memcpy(cfg->emailName, "admin000@pkmn.dion.ne.jp", sizeof(cfg->emailName));
    memcpy(cfg->smtpServer, "mail.pkmn.dion.ne.jp", sizeof(cfg->smtpServer));
    memcpy(cfg->popServer, "pop.pkmn.dion.ne.jp", sizeof(cfg->popServer));
    MobileNumberStore(cfg->config_slot[0].number, sizeof(cfg->config_slot[0].number), "0077487751");
    memcpy(cfg->config_slot[0].id, "DION DDI-POCKET", sizeof(cfg->config_slot[0].id));
    strncpy(gServerConfig.hostname, "localhost", sizeof(gServerConfig.hostname) - 1);
    memset(gServerConfig.loginPass, 0, sizeof(gServerConfig.loginPass));
    uint16_t checksum = 0;
    for(int i = 0; i < 0xc0 - 2; ++i) {
        checksum += buffer[i];
    }
    buffer[0xc0 - 2] = (checksum >> 8);
    buffer[0xc0 - 1] = (checksum & 0xff);
    fwrite(buffer, 1, sizeof(buffer), f);
}

bool MobileConfigRead(void* user, void* dest, uintptr_t offset, size_t size) {
    struct mobile_user_data* udata = user;
    FILE* f = fopen("mobile.bin", "rb");
    if(f == NULL) {
        printf("Couldn't load mobile.bin. Creating default mobile.bin.\n");
        FILE* temp = fopen("mobile.bin", "wb");
        MobileConfigCreateDefault(temp);
        fclose(temp);
        f = fopen("mobile.bin", "rb");
    }
    size_t read = fread(udata->config, 1, MOBILE_CONFIG_SIZE, f);
    while(read < MOBILE_CONFIG_SIZE) {
        read += fread(udata->config, 1, MOBILE_CONFIG_SIZE, f);
    }
    LoadMobileServerConfig(&gServerConfig, (struct mobile_config*)udata->config); // Try and overwrite default values from mobile config.
// Recalculate checksum.
    uint16_t checksum = 0;
    for(int i = 0; i < 0xc0 - 2; ++i) {
        checksum += udata->config[i];
    }
    udata->config[0xc0 - 2] = (checksum >> 8);
    udata->config[0xc0 - 1] = (checksum & 0xff);
    fclose(f);
    memcpy(dest, udata->config + offset, size);
    return true;
}

static void MobileConfigUpdateChecksum(struct mobile_user_data* udata) {
    uint16_t checksum = 0;
    for(int i = 0; i < 0xc0 - 2; ++i) {
        checksum += udata->config[i];
    }
    udata->config[0xc0 - 2] = (checksum >> 8);
    udata->config[0xc0 - 1] = (checksum & 0xff);
}

bool MobileConfigWrite(void* user, const void* src, uintptr_t offset, size_t size) {
    struct mobile_user_data* udata = user;
    memcpy(udata->config + offset, src, size);
    MobileConfigUpdateChecksum(udata);
    FILE* f = fopen("mobile.bin", "wb");
    fwrite(udata->config, 1, MOBILE_CONFIG_SIZE, f);
    fclose(f);
    return true;
}

void MobileSetDevice(int device, bool unmetered) {
    mobile_config_set_device(gMobileAdapter, device, unmetered);
}

void MobileInitSockets(struct mobile_user_data* udata) {
    socket_impl_init(udata);
}

void MobileInitTimers(struct mobile_user_data* udata) {
    for(int i = 0; i < MOBILE_MAX_TIMERS; ++i) {
        udata->timers[i] = SDL_GetTicks();
    }
}

void MobileDelSockets(struct mobile_user_data* udata) {
    socket_impl_stop(udata);
}

void MobileUpdate(void) {
    if(gMobileAdapter)
        mobile_loop(gMobileAdapter);
}

bool MobileCheckAdapterEnabled(void) {
    return gMobileAdapter != NULL;
}

bool MobileCheckSerialEnabled(void) {
    return MobileCheckAdapterEnabled() && ((gMobileData.flags & MOBILE_USER_ENABLED) != 0);
}

bool MobileCheckSerial32Bit(void) {
    return ((gMobileData.flags & MOBILE_USER_32BIT) != 0);
}

uint32_t MobileTransfer(uint32_t input) {
    if(MobileCheckSerial32Bit())
        return mobile_transfer_32bit(gMobileAdapter, input);
    else
        return mobile_transfer(gMobileAdapter, (uint8_t)input);
}

// Initialized emulated mobile adapter
void MobileInit(void) {
    gMobileAdapter = mobile_new(&gMobileData);
    // gMobileData.logpath = "mobile.log";

    mobile_def_debug_log(gMobileAdapter, MobileDebugLog);
    mobile_def_serial_enable(gMobileAdapter, MobileSerialEnable);
    mobile_def_serial_disable(gMobileAdapter, MobileSerialDisable);
    mobile_def_config_read(gMobileAdapter, MobileConfigRead);
    mobile_def_config_write(gMobileAdapter, MobileConfigWrite);
    mobile_def_sock_open(gMobileAdapter, socket_impl_open);
    mobile_def_sock_close(gMobileAdapter, socket_impl_close);
    mobile_def_sock_connect(gMobileAdapter, socket_impl_connect);
    mobile_def_sock_listen(gMobileAdapter, socket_impl_listen);
    mobile_def_sock_accept(gMobileAdapter, socket_impl_accept);
    mobile_def_sock_send(gMobileAdapter, socket_impl_send);
    mobile_def_sock_recv(gMobileAdapter, socket_impl_recv);
    mobile_def_time_latch(gMobileAdapter, MobileTimeLatch);
    mobile_def_time_check_ms(gMobileAdapter, MobileTimeCheckMs);

    mobile_config_load(gMobileAdapter);
    mobile_config_set_device(gMobileAdapter, MOBILE_ADAPTER_BLUE, true);
    struct mobile_addr dns = {.type = MOBILE_ADDRTYPE_IPV4};
    struct mobile_addr4* addr4 = (struct mobile_addr4*)&dns._addr4;
    addr4->host[0] = 1;
    addr4->host[1] = 1;
    addr4->host[2] = 1;
    addr4->host[3] = 1;
    addr4->port = MOBILE_DNS_PORT;
    mobile_config_set_dns(gMobileAdapter, &dns, MOBILE_DNS1);
    mobile_config_set_p2p_port(gMobileAdapter, MOBILE_PORT);
    mobile_config_set_relay(gMobileAdapter, &(struct mobile_addr){.type = MOBILE_ADDRTYPE_NONE});
    // mobile_config_save(gMobileAdapter);

    // struct mobile_addr relay = {.type = MOBILE_ADDRTYPE_IPV4};
    // addr4 = (struct mobile_addr4*)&relay._addr4;
    // addr4->host[0] = 127;
    // addr4->host[1] = 0;
    // addr4->host[2] = 0;
    // addr4->host[3] = 1;
    // addr4->port = MOBILE_DEFAULT_RELAY_PORT;
    // mobile_config_set_relay(gMobileAdapter, &relay);

    MobileInitSockets(&gMobileData);
    MobileInitTimers(&gMobileData);
    
    mobile_start(gMobileAdapter);
}

void MobileQuit(void) {
    mobile_stop(gMobileAdapter);

    MobileDelSockets(&gMobileData);

    free(gMobileAdapter);
    gMobileAdapter = NULL;
}

#else 

bool NetworkInit(void) {
    printf("Networking is not supported.\n");
    return false;
}

void NetworkDeinit(void) {

}

#endif
