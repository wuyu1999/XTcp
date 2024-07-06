#ifndef XUDP_H
#define XUDP_H
#include <string>
class XUdp
{
public:
    XUdp();
    ~XUdp();
    int CreateSocket();
    void Close();
    bool Bind(unsigned short port);
    int Recv(char *buf, int bufsize);
    //XUdp Accept();
    char ip[16];
    unsigned short port = 0;

    
    int Send(const char *buf, int sendsize);
    bool Connect(const char *ip, unsigned short port, int timeoutms = 1000);
    bool SetBlock(bool isblock);

protected:
    int sock = 0;

private:
    void *addr = 0;
};

#endif