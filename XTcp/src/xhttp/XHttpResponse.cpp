#include "XHttpResponse.h"
#include <string>
#include <regex>
using namespace std;

XHttpResponse::XHttpResponse(/* args */)
{
}

XHttpResponse::~XHttpResponse()
{
}

string XHttpResponse::GetHead()
{
    // 回应HTTP GET请求
    string rmsg = "";
    rmsg = "HTTP/1.1 200 OK\r\n";
    rmsg += "Server: XHttp\r\n";
    rmsg += "Content-Type: text/html\r\n";
    rmsg += "Content-Length: ";
    char bsize[128] = {0};
    sprintf(bsize, "%d", filesize);
    rmsg += bsize;
    rmsg += "\r\n";
    // rmsg += "10\r\n";
    rmsg += "\r\n";
    return rmsg;
}

bool XHttpResponse::SetRequest(std::string request)
{
    string src = request;
    // 匹配三种情况：/   /index.html     /ff
    string pattern = "^([A-Z]+) /([a-zA-Z0-9]*([.][a-zA-Z]*)?)[?]?(.*) HTTP/1";
    regex r(pattern);
    smatch mas;
    regex_search(src, mas, r);
    if (mas.size() == 0)
    {
        printf("%s failed!\n", pattern.c_str());
        return false;
    }

    string type = mas[1];
    string path = "/";
    path += mas[2];
    string filetype = mas[3];
    string query = mas[4];

    if (type != "GET")
    {
        printf("Not GET!\n");
        return false;
    }

    string filename = path;
    if (path == "/")
    {
        filename = "/index.html";
    }

    string filepath = "www";
    filepath += filename;

    if (filetype == "php")
    {
        // php-cgi www/index.php > www/index.php.html
        string cmd = "php-cgi ";
        cmd += filepath;
        cmd += ' ';
        // query id=1&name=xxx
        // id=1 name=xxx
        for (int i = 0; i < query.size(); i++)
        {
            if (query[i] == '&')
                query[i] = ' ';
        }
        cmd += query;

        cmd += " > ";
        filepath += ".html";
        cmd += filepath;

        printf("%s", cmd.c_str());
        system(cmd.c_str());
    }

    fp = fopen(filepath.c_str(), "rb");
    if (fp == NULL)
    {
        printf("open file %s failed!\n", filepath.c_str());
        return false;
    }
    // 获取文件大小
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    fseek(fp, 0, 0);
    printf("file size is %d\n", filesize);

    if (filetype == "php")
    {
        // 去除php头
        char c = 0;
        // \r\n\r\n
        int headsize = 0;
        while (fread(&c, 1, 1, fp) > 0)
        {
            headsize++;
            if (c == '\r')
            {
                fseek(fp, 3, SEEK_CUR);
                headsize += 3;
                break;
            }
        }

        filesize = filesize - headsize;
    }

    return true;
}

int XHttpResponse::Read(char *buf, int bufsize)
{
    // 发送正文
    return fread(buf, 1, bufsize, fp);
}