#pragma once
#include <string>
class XHttpResponse
{
private:
    int filesize = 0;
    FILE *fp = NULL;
public:
    XHttpResponse(/* args */);
    ~XHttpResponse();
    std::string GetHead();
    bool SetRequest(std::string request);
    int Read(char *buf, int bufsize);
    
};


