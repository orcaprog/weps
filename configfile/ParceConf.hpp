/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParceConf.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:54:35 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/08 17:26:54 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCECONF_HPP
#define PARCECONF_HPP


#include "Servers.hpp"
#include <sstream>
#include <vector>
#include <deque>
#include <map>
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
#include <unistd.h>
#include <errno.h>

#include "../elidrys/src/request.hpp"

#define MAX_EVENTS 1000
class ParceConf
{
private:
size_t index;
public:
    std::vector< Servers > Vservers;
    std::vector<std::vector<std::string> >  Vconf;
    // std::vector<std::pair<int,std::vector<std::string>>>  Vconf;
    Servers FirstFill();
    std::vector<std::string> Split_line(std::string line);

void Printtwodom(const std::vector<std::vector<std::string> > & matrix,std::string data);

    std::map<int ,Servers> mSclServ;
    std::map<int ,std::pair<Servers,request> > mClients;
    
    struct epoll_event ev;
    struct epoll_event events[MAX_EVENTS];
    int  conn_sock;
    int nfds;
    int  epollfd;

    std::map<int,Servers > msockets;    
    void FillServers();
    void desplay();
    void CreatMUltiplex();
    void Connect_And_Add(int n,const char * hello);

    ParceConf(std::string confgfile);
    ~ParceConf();
};




#endif