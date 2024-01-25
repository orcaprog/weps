/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParceConf.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:54:35 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/24 18:46:52 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCECONF_HPP
#define PARCECONF_HPP

#include  <string>
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

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Cgi.hpp"

#include "../elidrys/src/Request.hpp"

#define MAX_EVENTS 1000
class ParceConf
{
private:
    size_t index;
    std::vector< Servers > Vservers;
    std::vector<std::vector<std::string> >  Vconf;
    Servers FirstFill();
    std::vector<std::string> Split_line(std::string line);
    void FillServers();
    void desplay();
public:
    std::map<int,Servers > msockets;    
    void TakeAndParce(std::string confgfile);
    ParceConf();
    ~ParceConf();
};




#endif