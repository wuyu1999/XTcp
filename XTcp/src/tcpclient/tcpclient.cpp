#include "XTcp.h"

int main() 
{
    XTcp client;
    client.CreateSocket();
    client.SetBlock(false);
    client.Connect("192.168.111.128", 8080, 3000);
    client.Send("client", 6);
    char buf[1024] = {0};
    client.Recv(buf, sizeof(buf));
    printf("%s\n", buf);
    return 0;
}