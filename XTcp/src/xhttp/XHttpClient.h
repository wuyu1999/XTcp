#pragma once
#include "XTcp.h"
#include "XHttpResponse.h"
class XHttpClient
{
private:
    /* data */
public:
    XHttpClient(/* args */);
    ~XHttpClient();
    bool Start(XTcp client);
    void Main();
    XTcp client;
    XHttpResponse res;
};


