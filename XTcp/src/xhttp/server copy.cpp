#include <stdlib.h>
#include <thread>
#include <string.h>
#include <string>
#include <regex>
#include "XTcp.h"

using namespace std;

// class HttpThread
// {
// public:
//     void Main()
//     {
//         char buf[10000] = {0};
//         for (;;)
//         {
//             // 接受HTTP客户端请求
//             int recvLen = client.Recv(buf, sizeof(buf) - 1);
//             if (recvLen <= 0)
//             {
//                 Close();
//                 return;
//             }
//             buf[recvLen] = '\0';
//             printf("=======recv========\n%s\n===============\n", buf);

//             // GET /favicon.ico HTTP/1.1
//             // Host: 192.168.111.128:8080
//             // Connection: keep-alive
//             // User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36 Edg/126.0.0.0
//             // Accept: image/avif,image/webp,image/apng,image/svg+xml,image/*,*/*;q=0.8
//             // Referer: http://192.168.111.128:8080/
//             // Accept-Encoding: gzip, deflate
//             // Accept-Language: zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6

//             string src = buf;
//             // 匹配三种情况：/   /index.html     /ff
//             string pattern = "^([A-Z]+) /([a-zA-Z0-9]*([.][a-zA-Z]*)?)[?]?(.*) HTTP/1";
//             regex r(pattern);
//             smatch mas;
//             regex_search(src, mas, r);
//             if (mas.size() == 0)
//             {
//                 printf("%s failed!\n", pattern.c_str());
//                 Close();
//                 return;
//             }

//             string type = mas[1];
//             string path = "/";
//             path += mas[2];
//             string filetype = mas[3];
//             string query = mas[4];
//             if (filetype.size() > 0)
//                 filetype = filetype.substr(1, filetype.size() - 1);
//             printf("type=[%s]\npath=[%s]\nfilename=[%s]\nquery=[%s]\n",
//                    type.c_str(),
//                    path.c_str(),
//                    filetype.c_str(),
//                    query.c_str());

//             if (type != "GET")
//             {
//                 printf("Not GET");
//                 Close();
//                 return;
//             }

//             string filename = path;
//             if (path == "/")
//             {
//                 filename = "/index.html";
//             }

//             string filepath = "www";
//             filepath += filename;

//             if (filetype == "php")
//             {
//                 // php-cgi www/index.php > www/index.php.html
//                 string cmd = "php-cgi ";
//                 cmd += filepath;
//                 cmd += ' ';
//                 // query id=1&name=xxx
//                 // id=1 name=xxx
//                 for (int i = 0; i < query.size(); i++)
//                 {
//                     if (query[i] == '&')
//                         query[i] = ' ';            
//                 }
//                 cmd += query;

//                 cmd += " > ";
//                 filepath += ".html";
//                 cmd += filepath;
                
                
//                 printf("%s", cmd.c_str());
//                 system(cmd.c_str());
//             }

//             FILE *fp = fopen(filepath.c_str(), "rb");
//             if (fp == NULL)
//             {
//                 printf("open file %s failed!\n", filepath.c_str());
//                 Close();
//                 return;
//             }
//             // 获取文件大小
//             fseek(fp, 0, SEEK_END);
//             int filesize = ftell(fp);
//             fseek(fp, 0, 0);
//             printf("file size is %d\n", filesize);

//             if (filetype == "php")
//             {
//                 // 去除php头
//                 char c = 0;
//                 // \r\n\r\n
//                 int headsize = 0;
//                 while (fread(&c, 1, 1, fp) > 0)
//                 {
//                     headsize++;
//                     if (c == '\r')
//                     {
//                         fseek(fp, 3, SEEK_CUR);
//                         headsize += 3;
//                         break;
//                     }
//                 }

//                 filesize = filesize - headsize;
//             }

//             // 回应HTTP GET请求
//             string rmsg = "";
//             rmsg = "HTTP/1.1 200 OK\r\n";
//             rmsg += "Server: XHttp\r\n";
//             rmsg += "Content-Type: text/html\r\n";
//             rmsg += "Content-Length: ";
//             char bsize[128] = {0};
//             sprintf(bsize, "%d", filesize);
//             rmsg += bsize;
//             rmsg += "\r\n";
//             // rmsg += "10\r\n";
//             rmsg += "\r\n";
//             // rmsg += "0123456789";
//             //  发送消息头
//             int sendSize = client.Send(rmsg.c_str(), rmsg.size());
//             printf("sendSize = %d\n", sendSize);
//             printf("=======send========\n%s\n===============\n", rmsg.c_str());

//             // 发送正文
//             for (;;)
//             {
//                 int len = fread(buf, 1, sizeof(buf), fp);
//                 if (len <= 0)
//                     break;
//                 int re = client.Send(buf, len);
//                 if (re <= 0)
//                     break;
//             }
//         }

//         Close();
//     }
//     void Close()
//     {
//         client.Close();
//         delete this;
//     }
//     XTcp client;
// };

#include "XHttpServer.h"

int main(int argc, char *argv[])
{

    unsigned short port = 8080;
    if (argc > 1)
    {
        port = atoi(argv[1]);
    }

    XHttpServer server;
    server.Start(port);
    
    // XTcp server;
    // server.CreateSocket();
    // server.Bind(port);

    // for (;;)
    // {
    //     XTcp client = server.Accept();
    //     HttpThread *th = new HttpThread();
    //     th->client = client;
    //     std::thread sth(&HttpThread::Main, th);
    //     sth.detach();
    // }
    // server.Close();

    getchar();

    return 0;
}