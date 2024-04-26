#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "network.h"
#include "../home/delay.h"

#if defined(NETWORKING_SUPPORT)
#if defined(_MSC_VER)
#include <SDL_NET.h>
#else
#include <SDL2/SDL_net.h>
#endif
#include "../tools/emu/peanut_gb.h"
extern struct gb_s gb;

#if !(defined(__cplusplus) || defined(_MSC_VER))
#define static_assert _Static_assert
#endif

#define UDP_PORT 22600
#define TCP_PORT 22601

#define UDP_PACKET_SIZE 32

bool gNetworkingInit = false;
static UDPsocket host;
static UDPpacket* packet;
static TCPsocket serial;
static TCPsocket cserial;
static IPaddress localhost;
static uint32_t publicHost;

// A networking interface for suiCune. Supports both LAN (local) connections, emulating
// the standard link cable connection, and internet (remote) connections, emulating
// the mobile GB connection.
// Currently, mobile connections are not emulated, but will be in the future.

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
    uint32_t src;
    uint8_t type;
    union {
        struct {
            uint8_t name[10];
            uint16_t trainerId;
            uint8_t gender;
        } host_lan;
        struct {
            uint8_t name[10];
            uint16_t trainerId;
            uint8_t gender;
        } join_lan;
    };
} CmdPacket_s;

static_assert(sizeof(CmdPacket_s) <= UDP_PACKET_SIZE, "");

static void gb_serial_tx_test(const uint8_t x) {
    printf("serial send: %d\n", x);
}

static uint16_t HostToNet16(uint16_t x) {
    union {
        int a;
        char b[sizeof(int)];
    } test = {.a=1};
    if(test.b[0] == 1) {
        // little-endian
        return (x >> 8) | (x << 8);
    }
    return x;
}

static uint32_t HostToNet32(uint32_t x) {
    union {
        int a;
        char b[sizeof(int)];
    } test = {.a=1};
    if(test.b[0] == 1) {
        // little-endian
        return (x >> 24) 
            | ((x >> 8)  & 0x0000ff00)
            | ((x << 8)  & 0x00ff0000)
            | ((x << 24) & 0xff000000);
    }
    return x;
}

static enum gb_serial_rx_ret_e gb_serial_rx_test(uint8_t* x) {
    // receive byte
    *x = 0xff;
    return GB_SERIAL_RX_NO_CONNECTION;
}

#define MAX_TRIES_DETECT_PACKET_SENT 32

bool NetworkInit(void) {
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

        // Get public address using UDP broadcasting.
        // This is used to filter out packets we sent.
        uint32_t check = (uint32_t)time(NULL);
        *(uint32_t*)packet->data = HostToNet32(check);
        packet->len = sizeof(uint32_t);
        packet->address.host = HostToNet32(INADDR_BROADCAST);
        packet->address.port = HostToNet16(UDP_PORT);
        if(SDLNet_UDP_Send(host, -1, packet) == 0) {
            printf("Could not send UDP packet on port %d. Is the port blocked?\n", UDP_PORT);
            return false;
        }
        // Clear previous value.
        *(uint32_t*)packet->data = 0;

        // Perform some number of tries to get the packet off the network.
        // After that, it assumes the packet got lost.
        int tries = 0;
        do {
            while(SDLNet_UDP_Recv(host, packet) == 0) {
                SDL_Delay(1);
                tries++;
                if(tries > MAX_TRIES_DETECT_PACKET_SENT)
                    break;
            }

            // If the check value isn't what we expect, we reject it.
            if(HostToNet32(*(uint32_t*)packet->data) != check) {
                printf("WARNING: A problem occurred when trying to get this machine's IP address.\n");
                tries++;
                continue;
            }
            else {
                break;
            }
        } while(tries <= MAX_TRIES_DETECT_PACKET_SENT);
        printf("Public host: %d.%d.%d.%d\n", packet->address.host & 0xff,
            (packet->address.host >> 8) & 0xff,
            (packet->address.host >> 16) & 0xff,
            (packet->address.host >> 24) & 0xff);
        publicHost = packet->address.host;
        gNetworkingInit = true;
        gNetworkState = NETSTATE_NOTHING;
        gb.gb_serial_rx = gb_serial_rx_test;
        gb.gb_serial_tx = gb_serial_tx_test;
        return true;
    }
}

void gb_serial_tx(const uint8_t x) {
    // send byte
    SDLNet_TCP_Send(serial, &x, sizeof(x));
}

enum gb_serial_rx_ret_e gb_serial_rx(uint8_t* x) {
    // receive byte
    if(SDLNet_TCP_Recv(serial, x, 1) == 0) {
        return GB_SERIAL_RX_NO_CONNECTION;
    }
    return GB_SERIAL_RX_SUCCESS;
}

bool NetworkBroadcastLAN(const uint8_t* name, uint16_t id, uint8_t gender) {
    memset(packet->data, 0, UDP_PACKET_SIZE);
    CmdPacket_s* cmd = (CmdPacket_s*)packet->data;
    cmd->type = CMD_HOST_LAN;
    cmd->src = publicHost;
    memcpy(cmd->host_lan.name, name, 10);
    cmd->host_lan.trainerId = HostToNet16(id);
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
}

void NetworkStartJoining(void) {
    // Toss any packets waiting.
    while(SDLNet_UDP_Recv(host, packet) == 1) {}
    gNetworkState = NETSTATE_JOINING;
}

bool NetworkTryJoinLAN(uint8_t which, const uint8_t* name, uint16_t id, uint8_t gender) {
    if(which < gLANClientCandidateCount) {
        memset(packet->data, 0, UDP_PACKET_SIZE);
        CmdPacket_s* cmd = (CmdPacket_s*)packet->data;
        cmd->type = CMD_JOIN_LAN;
        cmd->src = publicHost;
        memcpy(cmd->host_lan.name, name, 10);
        cmd->host_lan.trainerId = HostToNet16(id);
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
        return true;
    }
    return false;
}

LANClient gLANClientCandidates[16];
uint32_t gLANClientCandidateCount;

bool NetworkTryRecvUDP(void) {
    int error = SDLNet_UDP_Recv(host, packet);
    if(error == -1) {
        printf("SDLNet: %s", SDLNet_GetError());
        return false;
    }
    return error == 1;
}

// Is this a duplicate of a host we already added?
static bool NetworkCheckDuplicateLANCandidate(uint32_t host) {
    for(uint32_t i = 0; i < gLANClientCandidateCount; ++i) {
        if(gLANClientCandidates[i].address == host)
            return true;
    }
    return false;
}

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
    memcpy(lan->name, cmd->host_lan.name, 10);
    lan->trainerId = HostToNet16(cmd->host_lan.trainerId);
    lan->gender = cmd->host_lan.gender;
    gLANClientCandidateCount++;
}

static bool NetworkTryAddLANCandidate(void) {
    if(NetworkCheckDuplicateLANCandidate(packet->address.host))
        return false;
    NetworkAddLANCandidate();
    return true;
}

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
    memcpy(lan->name, cmd->host_lan.name, 10);
    lan->trainerId = HostToNet16(cmd->host_lan.trainerId);
    lan->gender = cmd->host_lan.gender;
}

bool NetworkCheckLAN(void) {
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
        if(packet->address.host == publicHost)
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
}

void NetworkClearLANCache(void) {
    gLANClientCandidateCount = 0;
    memset(gLANClientCandidates, 0, sizeof(gLANClientCandidates));
}

bool NetworkLANDirectConnect(uint32_t which) {
    serial = SDLNet_TCP_Open(&(IPaddress){.host = INADDR_ANY, .port = HostToNet16(TCP_PORT)});
    packet->address.host = gLANClientCandidates[which].address;
    CmdPacket_s* cmd = (CmdPacket_s*)packet->data;
    cmd->type = CMD_ACCEPT_JOIN_LAN;
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
    gb.gb_serial_rx = gb_serial_rx;
    gb.gb_serial_tx = gb_serial_tx;
    return true;
}

bool NetworkAcceptLANConnection(void) {
    serial = SDLNet_TCP_Open(&(IPaddress){.host = packet->address.host, .port = HostToNet16(TCP_PORT)});
    if(serial != NULL) {
        gb.gb_serial_rx = gb_serial_rx;
        gb.gb_serial_tx = gb_serial_tx;
        return true;
    }
    printf("SDLNet: Error trying to connect to %d.%d.%d.%d\n",
        packet->address.host & 0xff, 
        (packet->address.host >> 8) & 0xff,
        (packet->address.host >> 16) & 0xff,
        (packet->address.host >> 24) & 0xff);
    return false;
}

void NetworkCloseConnection(void) {
    if(cserial) {
        SDLNet_TCP_Close(cserial);
        cserial = NULL;
    }
    if(serial) {
        SDLNet_TCP_Close(serial);
        serial = NULL;
    }
    gb.gb_serial_rx = gb_serial_rx_test;
    gb.gb_serial_tx = gb_serial_tx_test;
    gNetworkState = NETSTATE_NOTHING;
}

void NetworkDeinit(void) {
    if(gNetworkingInit) {
        if(packet != NULL) {
            SDLNet_FreePacket(packet);
        }
        if(host != NULL) {
            SDLNet_UDP_Close(host);
        }
        SDLNet_Quit();
    }
}

#else 

bool NetworkInit(void) {
    printf("Networking is not supported.\n");
    return false;
}

void NetworkDeinit(void) {

}

#endif
