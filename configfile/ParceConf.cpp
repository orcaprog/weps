/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParceConf.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:54:31 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/08 09:30:32 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParceConf.hpp"

std::vector<std::string> ParceConf::Split_line(std::string line)
{
    std::stringstream ss;
    std::vector<std::string> vline;
    index = 0;
    ss << line;
    std::string chunks;
    while (std::getline(ss,chunks,' '))
    {
        if(!chunks.empty())
            vline.push_back(chunks);
    }
    return vline;
}

ParceConf::ParceConf(std::string confgfile)
{
    std::ifstream configfile;
    std::string line;
    std::vector<std::string> _split;
    configfile.open(confgfile.c_str(), std::ios::in);
    if (configfile.is_open()) 
    {
        while (getline(configfile, line)) {
            
            if (!line.empty() )
            {
                _split = Split_line(line);
                if (!_split.empty())
                {
                    Vconf.push_back(_split);
                }
                
            }
        }
        configfile.close();
    }
}

Servers ParceConf::FirstFill()
{
    Servers server;
    // int bracket = 0;
    if (Vconf[index][0] != "server" || Vconf[index].size() > 1)
    {
        throw "Error : no server derectires";
    }
    else
        server.servconf.push_back(Vconf[index]);
    index++;
    
    // if (index < Vconf.size()  && Vconf[index][0] != "{")
    // {
    //     throw "Error : no open brackets \n";
    // }
    // index++;
    // bracket++;
    
    while (index < Vconf.size() && Vconf[index][0] != "server")
    {
        // if (Vconf[index][0] == "{")
        //     bracket++;

        server.servconf.push_back(Vconf[index]);
        index++;
    }
    // std::cout<<"_______br______"<<bracket<<std::endl;
    // if (Vconf[index - 1][0] != "}")
    // {
    //     throw "Error : no open brackets \n";
    // }
    
    return server;
}
void ParceConf::FillServers()
{
  
    
    std::vector<std::string> Vcol;
    std::vector<std::string>::iterator iter;

    // if(Vconf[0][0] != "server")
    // {
    //     throw "Error : no server derectires";
    // }
    // for (size_t i = 0; i < Vconf.size(); i++)
    // {
        
    //     Vcol = Vconf[i];
    //     Vservers[x].vconf.push_back(Vcol);
    // }
    while (index < Vconf.size())
    {
        Vservers.push_back(FirstFill());
    }
    
}

void ParceConf::desplay()
{
    FillServers();
    size_t i = 0;
    while (i < Vservers.size())
    {
        std::cout<<"###############################"<<std::endl;
        
        Vservers[i].SetAllDir();
        Vservers[i].CreatSocketServer();
        msockets[Vservers[i].server_fd] = Vservers[i].port[0];
        // Vservers[i].desplay();
        std::cout<<"###############################"<<std::endl;
        i++;
    }
    // for (size_t  i = 0; i < vsockets.size();i++)
    // {
    //     std::cout<<"sockets for server :"<<vsockets[i]<<std::endl;
    // }
    
    // std::vector<std::vector<std::string>> matrix =  Vservers[0].vconf;
    // for (const auto& row : matrix) {
    //     for (std::string value : row) {
    //         std::cout << value << "|";
    //     }
    //     std::cout << std::endl;
    // }
}
// void ParceConf::CreatSocketServer()
// {
    
// }
ParceConf::~ParceConf()
{
}

//  Vconf.push_back(std::pair<int, std::vector<std::string>>(0, Split_line(line)));
//      std::vector<std::pair<int,std::vector<std::string>>>  matrix =  Vconf;
//     std::cout<<"jdjdfjfj\n";
//     for (const auto& row : matrix) {
//         std::cout<<"key  :"<<row.first<<"  ";
//         for (std::string value : row.second) {
//             std::cout << value << "|";
//         }
//         std::cout << std::endl;
//     }


// void do_use_fd(int sockfd) {
//     char buffer[1024];
//     ssize_t bytesRead;

//     for (;;) {
//         // Read data from the socket
//         bytesRead = read(sockfd, buffer, sizeof(buffer));

//         if (bytesRead == -1) {
//             if (errno == EAGAIN || errno == EWOULDBLOCK) {
//                 // No more data available for now, exit the loop
//                 break;
//             } else {
//                 perror("read");
//                 // Handle other read errors
//                 break;
//             }
//         } else if (bytesRead == 0) {
//             // Connection closed by the client
//             // Perform cleanup or additional actions if needed
//             close(sockfd);
//             printf("Connection closed by client\n");
//             break;
//         } else {
//             // Process the received data
//             // Example: Print the received data
//             printf("Received data from socket %d: %.*s\n", sockfd, (int)bytesRead, buffer);
//         }
//     }

//     // Continue processing or return to the event loop
// }
void ParceConf::Connect_And_Add(int n,int port,const char * hello)
{
    struct sockaddr_in address; 
    int adrlen;
    ssize_t bytesRead = 0;
    char buffer[1024];
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( port );
    adrlen = sizeof(address);
    
    std::map<int, int>::iterator iter = msockets.find(events[n].data.fd );
    if (iter != msockets.end()) 
    {   
        // std::cout<<n<<std::endl;
        // std::cout<<"Enter server "<<events[n].data.fd<<" \n";
        conn_sock = accept(iter->first, (struct sockaddr *)&address, (socklen_t*)&adrlen);
        if (conn_sock == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        // setnonblocking(conn_sock);
        // if (fcntl(conn_sock, F_SETFL, fcntl(conn_sock, F_GETFL, 0) | O_NONBLOCK) == -1 )
        // {
        //             perror("fcntl F_SETFL O_NONBLOCK");
        //             exit(EXIT_FAILURE);
        // }


        ev.events = EPOLLIN | EPOLLET;
        ev.data.fd = conn_sock;
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock,&ev) == -1) 
        {
            perror("epoll_ctl: conn_sock");
            exit(EXIT_FAILURE);
        }
    } 
    else 
    {
        std::cout<<"Enter clinet "<<events[n].data.fd<<" \n";
         bytesRead = read(events[n].data.fd,buffer,sizeof(buffer));
        //mclinets[byteread] = requst(buffer);
        // get(request) 
        if (bytesRead == 0) 
        {
            close(events[n].data.fd);
            printf("Connection closed by client\n");
        }
        else 
        {
            printf("Received data from socket %d: %.*s\n", events[n].data.fd, (int)bytesRead, buffer);
            write(events[n].data.fd , hello , strlen(hello));
        }
        
        // do_use_fd(events[n].data.fd);
    }
    std::cout<<"Here for check timeout\n";   
}


void ParceConf::CreatMUltiplex()
{



         std::ifstream inputFile;
     inputFile.open("index.html");
     std::string line;
     std::string data= "";
    while (std::getline(inputFile, line)) {
        data += line;
    }
    std::string headers = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 10000\r\n\r\n";
    std::string httprespose = headers + data;
    const char *hello = httprespose.c_str();


    

    epollfd = epoll_create1(0);
    if (epollfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }
    std::map<int,int>::iterator iter;

    for (iter = msockets.begin(); iter != msockets.end(); iter++)
    {
        ev.events = EPOLLIN;
        ev.data.fd = iter->first;
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, iter->first, &ev) == -1) {
            perror("epoll_ctl: listen_sock");
            exit(EXIT_FAILURE);
        }
    }
    while (true)
    {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }
        
        // for (iter = msockets.begin(); iter != msockets.end(); iter++)
        // {
            for (int n = 0; n < nfds ; ++n) 
            {
                
                // std::cout<<"nfds :"<<nfds<<"n :"<<n<<std::endl;
                std::cout<<"____________________________________________________\n";
                Connect_And_Add(n,iter->second,hello);
                std::cout<<"____________________________________________________\n";
            }
        // }
    }

}