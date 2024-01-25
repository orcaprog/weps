/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:42:27 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/25 18:14:03 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERS_HPP
#define SERVERS_HPP

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <algorithm> 
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <map>
#include <sys/stat.h>
#include "Location.hpp"
#include <stack>

class Servers
{
private:
  


    std::vector<std::string>  AddErrorPage(std::string status,std::string path);
    int  checkDup(std::string der,int & index);
    bool check_isdigit(std::string str);
    void FillStatus();
    void FillValid();
    void checkValidation();
    void parceIp(std::string ip);
    void check_Status(std::string status);

    int  pathExists(std::string path);

    int pathIsFile(std::string path);
    size_t GetIndex(std::string dir);
    
    Location FirstFill(size_t & index);
    
    void SetPorts (); // done ~
    void SetServerName(); // done ~
    void SetHost();  // done ~
    void SetRoot();  // done ~
    void SetError_page(); // done ~
    void SetClient_max_body_size(); // done ~
    void SetIndex(); // done ~
    
    void Printtwodom(const std::vector<std::vector<std::string> > & matrix,std::string data);
    void ReplacePath(std::string status,std::string path);

public:

    std::vector<int> port;
    std::vector<std::string> server_name; 
    std::vector<std::string> host; 
    std::vector<std::string> root;
    std::vector<std::string> index;
    std::vector<long long int > client_max_body_size;
    map<string,string> error_page;
    std::vector<std::string> s_erorr;


    int server_fd;
    struct sockaddr_in address;
    std::vector<std::string> Vstrvalid;
    std::vector<std::vector<std::string> > servconf;
    //________________________//
    //________loaction________//
    
    std::vector<Location> locations;

    //________________________//
    void SetAllDir();
    void desplay();
    
    const int & GetPorts (); 
    const std::string & GetServerName(); 
    const std::string & GetHost();  
    const std::string & GetRoot();  
    const std::vector<std::vector<std::string> >&  GetError_page(); 
    const long long int  &  GetClient_max_body_size(); 
    const std::string & GetIndex(); 

    int getLocation(std::string path);
    void SetDefaultError();
    void CreatSocketServer();
    Servers();

    /*====================================*/
    int searchPathLocation(string & uri);
    int fillFromLocation(int & index,string & uri);
    void FillData(string  uri);
    string rootUri;
    bool Is_cgi;
    void checkIsCgi(string uri);
    string querys;
    Location UriLocation;
    /*====================================*/
    void FillLocation();

    ~Servers();
};


#endif