#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>  
#include <sys/socket.h>

using namespace std;

int main(int argc, char *argv[])
{
    unsigned short port = 8080;
    if (argc > 1)
    {
        port = atoi(argv[1]);
    }
    
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock <= 0)
    {
        cout << "create socket failed!" << endl;
        return -1;
    }
    
    sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = htonl(0);

    if (::bind(sock, (sockaddr*)&saddr, sizeof(saddr)) != 0)
    {
        cout << "bind port" << port << "falied!" << endl;
        return -2;
    }
    cout << "bind port" << port << "success!" << endl;

    listen(sock, 10);
    sockaddr_in client;
    socklen_t len = sizeof(client);
    char buf[10240] = {0};
    // ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
    //                   struct sockaddr *src_addr, socklen_t *addrlen);
    int re = recvfrom(sock, buf, sizeof(buf), 0, (sockaddr*)&client, &len);
    if (re <= 0)
    {
        cout << "recvfrom failed!" << endl;
        return -3;
    }
    cout << "recv" << inet_ntoa(client.sin_addr) << ":" << ntohs(client.sin_port) << endl;

    buf[re] = '\0';

    cout << buf << endl;
    sendto(sock, "67890", 5, 0, (sockaddr*)&client, sizeof(client));
    getchar();
    return 0;
}