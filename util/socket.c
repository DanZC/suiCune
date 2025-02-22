// SPDX-License-Identifier: GPL-3.0-or-later
// "Borrowed" from libmobile-bgb
#include "socket.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

#if defined(__unix__)
#include <arpa/inet.h>
#include <poll.h>
#include <fcntl.h>
#include <netdb.h>
#endif

// Print last socket-related error
void socket_perror(const char *func)
{
    if (func) fprintf(stderr, "%s: ", func);
#if defined(__unix__)
    char error[0x100];
    if (strerror_r(errno, error, sizeof(error))) {
        putc('\n', stderr);
        return;
    }
    fprintf(stderr, "%s\n", error);
#elif defined(_WIN32)
    LPWSTR error = NULL;
    if (!FormatMessageW(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, WSAGetLastError(), 0, (LPWSTR)&error, 0, NULL)) {
        putc('\n', stderr);
        return;
    }
    fprintf(stderr, "%ls", error);
    LocalFree(error);
#endif
}

// Convert a sockaddr to a printable string
int socket_straddr(char *res, unsigned res_len, struct sockaddr *addr, socklen_t addrlen)
{
#if defined(__unix__)
    (void)addrlen;

    void *inaddr;
    unsigned inport;
    if (addr->sa_family == AF_INET) {
        struct sockaddr_in *addr4 = (struct sockaddr_in *)addr;
        inaddr = &addr4->sin_addr;
        inport = ntohs(addr4->sin_port) & 0xFFFF;
    } else if (addr->sa_family == AF_INET6) {
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)addr;
        inaddr = &addr6->sin6_addr;
        inport = ntohs(addr6->sin6_port) & 0xFFFF;
    } else {
        return -1;
    }

    if (!inet_ntop(addr->sa_family, inaddr, res, res_len)) return -1;
    size_t pos = strlen(res);
    snprintf(res + pos, res_len - pos, ":%u", inport);
#elif defined(_WIN32)
    DWORD res_len_r = res_len;
    if (WSAAddressToStringA(addr, addrlen, NULL, res, &res_len_r)
            == SOCKET_ERROR) {
        // Errors when the buffer isn't large enough as well
        return -1;
    }
#endif
    return 0;
}

// Check if a socket has data in the receive buffer (or an error)
int socket_hasdata(SOCKET socket)
{
#ifdef SOCKET_USE_POLL
    struct pollfd fd = {.fd = socket, .events = POLLIN | POLLPRI};
    int rc = poll(&fd, 1, 0);
    if (rc == -1) socket_perror("poll");
    return rc;
#else
    fd_set rfds, exfds;
    FD_ZERO(&rfds);
    FD_ZERO(&exfds);
    FD_SET(socket, &rfds);
    FD_SET(socket, &exfds);
    struct timeval tv = {0};
    int rc = select((int)socket + 1, &rfds, NULL, &exfds, &tv);
    if (rc == -1) socket_perror("select");
    return rc;
#endif
}

// Check if a connect() call has completed
int socket_isconnected(SOCKET socket)
{
#ifdef SOCKET_USE_POLL
    struct pollfd fd = {.fd = socket, .events = POLLOUT};
    int rc = poll(&fd, 1, 0);
    if (rc == -1) socket_perror("poll");
    if (rc <= 0) return rc;
#else
    fd_set wfds;
    FD_ZERO(&wfds);
    FD_SET(socket, &wfds);
    struct timeval tv = {0};
    int rc = select((int)socket + 1, NULL, &wfds, NULL, &tv);
    if (rc == -1) socket_perror("select");
    if (rc <= 0) return rc;
#endif

    // Get the error number that actually occurred
    int err;
    socklen_t err_len = sizeof(err);
    getsockopt(socket, SOL_SOCKET, SO_ERROR, (char *)&err, &err_len);
    socket_seterror(err);
    if (err) return -1;
    return 1;
}

// Wait on one or more sockets to become readable
int socket_wait(SOCKET *sockets, unsigned count, int delay)
{
#ifdef SOCKET_USE_POLL
    struct pollfd fds[count];
    for (unsigned i = 0; i < count; i++) {
        fds[i] = (struct pollfd){.fd = sockets[i], .events = POLLIN};
    }
    int rc = poll(fds, count, delay);
    if (rc == -1) socket_perror("poll");
    return rc;
#else
    SOCKET maxfd = 0;
    fd_set rfds;
    FD_ZERO(&rfds);
    for (unsigned i = 0; i < count; i++) {
        maxfd = max(sockets[i], maxfd);
        FD_SET(sockets[i], &rfds);
    }

    struct timeval tv = {
        .tv_sec = delay / 1000,
        .tv_usec = (delay % 1000) * 1000
    };
    int rc = select((int)maxfd + 1, &rfds, NULL, NULL, &tv);
    if (rc == -1) socket_perror("select");
    return rc;
#endif
}

// Set whether connect() and recv() calls on a socket block
int socket_setblocking(SOCKET socket, int flag)
{
#if defined(__unix__)
    int flags = fcntl(socket, F_GETFL);
    if (flags == -1) {
        perror("fcntl");
        return -1;
    }
    flags &= ~O_NONBLOCK;
    if (!flag) flags |= O_NONBLOCK;
    if (fcntl(socket, F_SETFL, flags) == -1) {
        perror("fcntl");
        return -1;
    }
#elif defined(_WIN32)
    u_long mode = !flag;
    if (ioctlsocket(socket, FIONBIO, &mode) == SOCKET_ERROR) return -1;
#endif
    return 0;
}

// Connect a socket to a user-provided hostname and port
SOCKET socket_connect(const char *host, const char *port)
{
    struct addrinfo hints = {
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM,
        .ai_protocol = IPPROTO_TCP
    };
    struct addrinfo *result;
    int gai_errno = getaddrinfo(host, port, &hints, &result);
    if (gai_errno) {
#if defined(__unix__)
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai_errno));
#elif defined(_WIN32)
        fprintf(stderr, "getaddrinfo: Error %d: ", gai_errno);
        socket_perror(NULL);
#endif
        return INVALID_SOCKET;
    }

    SOCKET sock = INVALID_SOCKET;
    int error = 0;
    struct addrinfo *info;
    for (info = result; info; info = info->ai_next) {
        errno = 0;
        sock = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
        if (sock == INVALID_SOCKET) {
            socket_perror("socket");
            continue;
        }
        if (connect(sock, info->ai_addr, (int)info->ai_addrlen) == 0) break;
        error = socket_geterror();
        socket_close(sock);
    }
    freeaddrinfo(result);
    socket_seterror(error);
    if (!info) return INVALID_SOCKET;
    return sock;
}

int resolve_host(const char* host, const char* port, struct sockaddr* addr) 
{
    struct addrinfo hints = {
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM,
        .ai_protocol = IPPROTO_TCP
    };
    struct addrinfo *result;
    int gai_errno = getaddrinfo(host, port, &hints, &result);
    if (gai_errno) {
#if defined(__unix__)
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai_errno));
#elif defined(_WIN32)
        fprintf(stderr, "getaddrinfo: Error %d: ", gai_errno);
        socket_perror(NULL);
#endif
        return 0;
    }
    struct addrinfo *info = result;
    memcpy(addr, info->ai_addr, info->ai_addrlen);
    freeaddrinfo(result);
    return 1;
}
