#pragma once

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define #define CLOSESOCKET(s) closesocket(s)
#else
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#define SOCKET int
#define ISVALIDSOCKET(s) ((s) >= 0)
#define SOCKET_ERROR -1
#define CLOSESOCKET(s) close(s)
#endif

#include <string>
#include <stdio.h>

namespace yl_sock
{
    class Tcp_socket
    {
    private:
        SOCKET cfd;

    public:
        Tcp_socket();
        void connect(const std::string &, const int) const;

        template <typename T>
        void send(const T *, const size_t) const;
        template <typename T>
        size_t receive(T *, const size_t) const;
        ~Tcp_socket();
    };
};

yl_sock::Tcp_socket::Tcp_socket()
{
#ifdef _WIN32

    WSDATA wsa;

    fprintf(stderr ,"\nInitialising Winsock...");

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        fprintf(stderr ,"Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    fprintf(stderr ,"Initialised.\n");

#endif

    this->cfd = socket(AF_INET, SOCK_STREAM, 0);

    if (!ISVALIDSOCKET(this->cfd))
    {
        fprintf(stderr, "socket() Failed!\n");
    }
}

void yl_sock::Tcp_socket::connect(const std::string & ip, const int port) const
{
    struct sockaddr_in server;

    server.sin_addr.s_addr = inet_addr(ip.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (::connect(this->cfd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        fprintf(stderr ,"connect() Failed!\n");
    }
}

template <typename T>
void yl_sock::Tcp_socket::send(const T * buf, const size_t size) const
{
    if (::send(this->cfd, buf, size, 0) < 0)
    {
        fprintf(stderr, "send() Failed!\n");
    }
}

template <typename T>
size_t yl_sock::Tcp_socket::receive(T * buf, const size_t size) const
{
    size_t recv_size;

    if ((recv_size = ::recv(this->cfd, buf, size, 0)) == SOCKET_ERROR)
    {
        fprintf(stderr, "recv() Failed!\n");

        return SOCKET_ERROR;
    }

    return recv_size;
}

yl_sock::Tcp_socket::~Tcp_socket()
{
    CLOSESOCKET(this->cfd);

#ifdef _WIN23
    WSACleanup();
#endif
}