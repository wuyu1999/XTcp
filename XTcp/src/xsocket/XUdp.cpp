#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <iostream>
#include <fcntl.h>
#include "XUdp.h"

using namespace std;

XUdp::XUdp()
{
    memset(ip, 0, sizeof(ip));
}

XUdp::~XUdp()
{

}

int XUdp::CreateSocket()
{
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
    {
        printf("create socket failed!/n");
    }
    return sock;
}

void XUdp::Close()
{
    if (sock <= 0)
        return;
    close(sock);
    if (addr)
        delete addr;
    addr = 0;
    sock = 0;
}

bool XUdp::Bind(unsigned short port)
{
    if (sock <= 0)
    {
        CreateSocket();
    }

    sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = htonl(0);

    if (bind(sock, (sockaddr *)&saddr, sizeof(saddr)) != 0)
    {
        printf("bind port %d failed!\n", port);
        return false;
    }
    printf("bind port %d success!\n", port);

    listen(sock, 10); // 10代表套接字队列的长度，并非并发的数量
    return true;
}

int XUdp::Recv(char *buf, int bufsize)
{
    if (sock <= 0)
    {
        return 0;
    }
    
    if (addr = 0)
    {
        addr = new sockaddr_in();
    }
    socklen_t len = sizeof(sockaddr_in);
    int re = recvfrom(sock, buf, bufsize, 0, (sockaddr*)addr, &len);
    return re;
}