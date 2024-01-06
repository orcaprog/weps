/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:43:48 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/06 12:03:05 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
#define PORT 8888

#include <unistd.h>
#include <errno.h>
void do_use_fd(int sockfd) {
    char buffer[1024];
    ssize_t bytesRead;

    // for (;;) {
    //     // Read data from the socket
        bytesRead = read(sockfd, buffer, sizeof(buffer));

    //     if (bytesRead == -1) {
    //         if (errno == EAGAIN || errno == EWOULDBLOCK) {
    //             // No more data available for now, exit the loop
    //             break;
    //         } else {
    //             perror("read");
    //             // Handle other read errors
    //             break;
    //         }
    //     } else if (bytesRead == 0) {
    //         // Connection closed by the client
    //         // Perform cleanup or additional actions if needed
    //         close(sockfd);
    //         printf("Connection closed by client\n");
    //         break;
    //     } else {
    //         // Process the received data
    //         // Example: Print the received data
            printf("Received data from socket %d: %.*s\n", sockfd, (int)bytesRead, buffer);
            
    //     }
    // }

    // Continue processing or return to the event loop
}
int main ()
{

    int fd =open("file",O_RDWR);
    // if (fcntl(0, F_SETFL, fcntl(0, F_GETFL, 0) | O_NONBLOCK) == -1 )
    // {
    //             perror("fcntl F_SETFL O_NONBLOCK");
    //             exit(EXIT_FAILURE);
    // }
    do_use_fd(0);
}