// Server side C program to demonstrate Socket programming
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <string.h>
#include <fcntl.h>
    #define MAX_EVENTS 10
#define PORT 3333
void setnonblocking(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl F_GETFL");
        exit(EXIT_FAILURE);
    }

    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL O_NONBLOCK");
        exit(EXIT_FAILURE);
    }
}
#include <unistd.h>
#include <errno.h>

// Placeholder for handling data on a connected socket
void do_use_fd(int sockfd) {
    char buffer[1024];
    ssize_t bytesRead;

    for (;;) {
        // Read data from the socket
        bytesRead = read(sockfd, buffer, sizeof(buffer));

        if (bytesRead == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // No more data available for now, exit the loop
                break;
            } else {
                perror("read");
                // Handle other read errors
                break;
            }
        } else if (bytesRead == 0) {
            // Connection closed by the client
            // Perform cleanup or additional actions if needed
            close(sockfd);
            printf("Connection closed by client\n");
            break;
        } else {
            // Process the received data
            // Example: Print the received data
            printf("Received data from socket %d: %.*s\n", sockfd, (int)bytesRead, buffer);
        }
    }

    // Continue processing or return to the event loop
}

int main(int argc, char const *argv[])
{
    int listen_sock, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
     std::ifstream inputFile;
     inputFile.open("index.html");
     std::string line;
     std::string data= "";
    while (std::getline(inputFile, line)) {
        data += line;
    }
    std::string headers = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 100\r\n\r\n Hello world";
    std::string httprespose = headers ;
    const char *hello = httprespose.c_str();
    // Creating socket file descriptor
    if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    if (bind(listen_sock, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(listen_sock, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    // while(1)
    // {
    //     printf("\n+++++++ Waiting for new connection ++++++++\n\n");
    //     if ((new_socket = accept(listen_sock, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
    //     {
    //         perror("In accept");
    //         exit(EXIT_FAILURE);
    //     }
        
    //     char buffer[30000] = {0};
    //     valread = read( new_socket , buffer, 30000);
    //     printf("%s\n",buffer );
    //     write(new_socket , hello , strlen(hello));
    //     printf("------------------Hello message sent-------------------\n");
    //     close(new_socket);
    // }


struct epoll_event ev, events[MAX_EVENTS];
int  conn_sock, nfds, epollfd;

           /* Code to set up listening socket, 'listen_sock',
              (socket(), bind(), listen()) omitted. */

epollfd = epoll_create1(0);
if (epollfd == -1) {
    perror("epoll_create1");
    exit(EXIT_FAILURE);
}

ev.events = EPOLLIN;
ev.data.fd = listen_sock;
if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
    perror("epoll_ctl: listen_sock");
    exit(EXIT_FAILURE);
}

for (;;) {
    nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
    if (nfds == -1) {
        perror("epoll_wait");
        exit(EXIT_FAILURE);
    }

    for (int n = 0; n < nfds ; ++n) {
        if (events[n].data.fd == listen_sock) {
            conn_sock = accept(listen_sock, (struct sockaddr *)&address, (socklen_t*)&addrlen);
            if (conn_sock == -1) {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            setnonblocking(conn_sock);
            ev.events = EPOLLIN | EPOLLET;
            ev.data.fd = conn_sock;
            if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock,
                        &ev) == -1) {
                perror("epoll_ctl: conn_sock");
                exit(EXIT_FAILURE);
            }
        } else {
            do_use_fd(events[n].data.fd);
        }
    }
}
    return 0;
}