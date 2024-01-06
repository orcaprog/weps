// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 3333
void creat_client(){
    int sock = 0; long valread;
    struct sockaddr_in serv_addr;
    char *hello = "GET /index.html HTTP/1.1\r\n\r\n   hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return ;
    }
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return ;
    }
    
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return ;
    }
    send(sock , hello , strlen(hello) , 0 );
    // printf("Hello message sent\n");
    // do
    // {
    //     valread = read( sock , buffer, 1024);
    //     printf("%s\n",buffer );
    // }while (valread == 1024);
    return ;
}
int main(int argc, char const *argv[])
{
    creat_client();
    creat_client();
}