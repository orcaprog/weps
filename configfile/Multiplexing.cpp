/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiplexing.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:04:44 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/23 19:02:42 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Multiplexing.hpp"

Multiplexing::Multiplexing(std::string  configfile)
{
    server.TakeAndParce(configfile);
    fd = -2;
}

Multiplexing::~Multiplexing()
{
}

std::string Multiplexing::chekIf(bool check)
{
    if (check)
        return "";
    else
        return  "Content-type: text/html\r\n\r\n"; 
}
bool Multiplexing::checkvalidHeader(std::string str)
{
    size_t pos;
    pos = str.find("Content-type:");
    if (pos == string::npos)
    {
        return 0;
    }
    if (pos != 0)
    {
        return 0;
    }
    pos = str.find("\r\n");
    if (pos == string::npos)
    {
        return 0;
    }
    return 1;
}

void Multiplexing::Out_Events(int n)
{
    char cgiBuffer[1024];
    std::string cgires("");
    string globRusl;

    if (mClients[events[n].data.fd].second.req_done())
    {
        if (fd != -2)
        {
            int readb = 1;
            bool check_cont;
            while (readb != 0)
            {
                readb = read(fd,cgiBuffer,1024);
                cout<<"read byts :"<<readb<<endl;
                cout<<"fd  :"<<fd<<endl;
                if (readb == 0)
                    break;
                std::cout<<"fd != -2   fd :"<<fd<<"\n";
                if (readb == -1)
                {
                    perror("Erorr read in cgi\n");
                    exit(1);
                }
                cgires.append(cgiBuffer,readb);
            }
            std::cout<<"enter here :"<<cgires<<endl;
            check_cont = checkvalidHeader(cgires);
            std::cout<<check_cont<<endl;
            globRusl = "HTTP/1.1 200 OK\r\n" + chekIf(check_cont) + cgires;
            write(events[n].data.fd,globRusl.c_str(),globRusl.length());
            epoll_ctl(epollfd,EPOLL_CTL_DEL,events[n].data.fd,&ev);
            close(fd);
            close(events[n].data.fd);
            mClients.erase(events[n].data.fd);
            fd = -2;
        }
        else
        {
            mClients[events[n].data.fd].second.process_req(string(""),0,EPOLLOUT);

            string res = mClients[events[n].data.fd].second.get_respons();

            write(events[n].data.fd , res.c_str(), res.size());
            if (mClients[events[n].data.fd].second.method && mClients[events[n].data.fd].second.method->end)
            {
                epoll_ctl(epollfd,EPOLL_CTL_DEL,events[n].data.fd,&ev);
                close(events[n].data.fd);
                mClients.erase(events[n].data.fd);
                cout<<"close connections :"<<events[n].data.fd<<endl;
            }
        }
    }
}

void Multiplexing::In_Events(int n)
{
    char buffer[1024];
    ssize_t bytesRead = 0;

    std::cout<<"Enter clinet "<<events[n].data.fd<<" \n";
    bytesRead = read(events[n].data.fd,buffer,1024);
    
    std::cout<<"size :"<<bytesRead<<std::endl;
    if (bytesRead == -1)
    {
        perror("Error read\n");
        return ;
    }
    if (bytesRead == 0) 
    {
        close(events[n].data.fd);
        std::cout<<"Connection closed by client\n"; 
    }
    else 
    {
        std::map<int ,std::pair<Servers,Request> >::iterator iter2 = mClients.find(events[n].data.fd);
        if (iter2 != mClients.end())
        {
            
            mClients[events[n].data.fd].second.process_req(string("").append(buffer, bytesRead),bytesRead,EPOLLIN);
            mClients[events[n].data.fd].first.FillData(mClients[events[n].data.fd].second.r_path);
            cout<<"rootUri :"<<mClients[events[n].data.fd].first.rootUri<<endl;
            cout<<"is_cgi :"<<mClients[events[n].data.fd].first.Is_cgi<<endl;


            // if (mClients[events[n].data.fd].second.r_path == "/favicon.ico")
            // {
            //     epoll_ctl(epollfd,EPOLL_CTL_DEL,events[n].data.fd,&ev);
            //     close(events[n].data.fd);
            //     mClients.erase(events[n].data.fd);
            //     cout<<"close connections :"<<events[n].data.fd<<endl;
            // }
            
            // if (mClients[events[n].data.fd].second.r_path.find("/cgi") != std::string::npos)
            // {
            //     Cgi cgi(mClients[events[n].data.fd].second.r_path,mClients[events[n].data.fd].first.getLocation("/cgi"));
            //     std::cout<<"enter here\n";
            //     cgi.ExecCgi();
            //     fd  = open("out.txt",O_RDONLY);
            // }
        }
    }
}

void Multiplexing::Connect_And_Add(int n)
{
    int adrlen;
    std::map<int, Servers>::iterator iter = server.msockets.find(events[n].data.fd );
    if (iter != server.msockets.end()) 
    {   
        adrlen = sizeof(iter->second.address);
        conn_sock = accept(iter->first, (struct sockaddr *)&iter->second.address, (socklen_t*)&adrlen);
        if (conn_sock == -1) 
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        mClients[conn_sock].first = iter->second;
        Request req(mClients[conn_sock].first.root[0]);
        mClients[conn_sock].second = req;
        std::cout<<"Fd Server :"<<iter->first<<std::endl;
        ev.events = EPOLLIN | EPOLLOUT;
        ev.data.fd = conn_sock;
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock,&ev) == -1) 
        {
            perror("epoll_ctl: conn_sock");
            exit(EXIT_FAILURE);
        }
    } 
    else 
    {
        if (events[n].events & EPOLLIN) 
        {
            In_Events(n);
        }
        else if (events[n].events & EPOLLOUT && mClients.find(events[n].data.fd) !=  mClients.end()) 
        {
            Out_Events(n);
        }
    }
}


void Multiplexing::CreatMUltiplex()
{
    std::ifstream inputFile;
    inputFile.open("index.html");
    std::string line;
    std::string data= "";
    while (std::getline(inputFile, line)) {
        data += line;
    }
    // std::string headers = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 1000000\r\n\r\n";
    // std::string httprespose = headers + data;
    // const char *hello = httprespose.c_str();

    epollfd = epoll_create(255);
    if (epollfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }
    std::map<int,Servers>::iterator iter;

    for (iter = server.msockets.begin(); iter != server.msockets.end(); iter++)
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
        // std::cout<<"nfds   :"<<nfds<<std::endl;
        if (nfds == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }
        
        for (int n = 0; n < nfds ; ++n) 
        {
            Connect_And_Add(n);
        }
    }

}