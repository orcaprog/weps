#include <iostream>
#include <cstring>
#include <sys/epoll.h>
#include <unistd.h>

using namespace std;

bool checkvalidHeader(std::string str)
{
    size_t pos;
    pos = str.find("Content-Type:");
    if (pos == string::npos)
    {
        return 0;
    }
    if (pos != 0)
    {
        return 0;
    }
    pos = str.find("\r\n");
    return 1;
}
int main()
{
    cout<<checkvalidHeader("Content-Type: text/html\r\nContent-Length: 1000000\r\n\r\n")<<"|"<<endl;
}