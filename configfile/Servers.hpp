/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:42:27 by abouassi          #+#    #+#             */
/*   Updated: 2023/12/30 12:22:23 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERS_HPP
#define SERVERS_HPP

#include <algorithm> 
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <map>
#include <sys/stat.h>
class Servers
{
private:
    std::vector<int> port;
    std::vector<std::string> server_name; 
    std::vector<std::string> host; 
    std::vector<std::string> root;
public:
    std::vector<std::string> Vstrvalid;
    std::vector<std::vector<std::string> > servconf;

    
    
    void desplay();
    int  checkDup(std::string der,int & index);
    bool check_isdigit(std::string str);

    void FillValid();
    void checkValidation();
    void parceIp(std::string ip);
    int  pathExists(std::string path);
    
    void SetPorts (); // done ~
    void SetServerName(); // done ~
    void SetHost();  // done ~
    void SetRoot();  
    void SetError_page();
    void SetClient_max_body_size();
    void SetIndex();
    
    Servers();
    ~Servers();
};


#endif