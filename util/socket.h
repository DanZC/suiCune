// SPDX-License-Identifier: GPL-3.0-or-later
// "Borrowed" from libmobile-bgb
#pragma once

#include <errno.h>

#if defined(__unix__)
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#elif defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#error "Unsupported OS"
#endif

#if defined(__unix__)
#define socket_close close
#define socket_geterror() errno
#define socket_seterror(e) errno = (e)
#define SOCKET_EWOULDBLOCK EWOULDBLOCK
#define SOCKET_EINPROGRESS EINPROGRESS
#define SOCKET_EALREADY EALREADY
#define SOCKET_EISCONN EISCONN
#define SOCKET_ERROR (-1)
#define INVALID_SOCKET (-1)
typedef int SOCKET;
#define SOCKET_USE_POLL
#elif defined(_WIN32)
#define socket_close closesocket
#define socket_geterror() WSAGetLastError()
#define socket_seterror(e) WSASetLastError(e)
#define SOCKET_EWOULDBLOCK WSAEWOULDBLOCK
#define SOCKET_EINPROGRESS WSAEINPROGRESS
#define SOCKET_EALREADY WSAEALREADY
#define SOCKET_EISCONN WSAEISCONN
#endif

// ipv6 addr + colon + 5 char port + terminator
#define SOCKET_STRADDR_MAXLEN (INET6_ADDRSTRLEN + 7)

void socket_perror(const char *func);
int socket_straddr(char *res, unsigned res_len, struct sockaddr *addr, socklen_t addrlen);
int socket_hasdata(SOCKET socket);
int socket_isconnected(SOCKET socket);
int socket_wait(SOCKET *sockets, unsigned count, int delay);
int socket_setblocking(SOCKET socket, int flag);
SOCKET socket_connect(const char *host, const char *port);
