/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:42:27 by abouassi          #+#    #+#             */
/*   Updated: 2023/12/31 12:09:02 by abouassi         ###   ########.fr       */
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
#include "Location.hpp"
class Servers
{
private:
    std::vector<int> port;
    std::vector<std::string> server_name; 
    std::vector<std::string> host; 
    std::vector<std::string> root;
    std::vector<std::string> index;
    std::vector<long long int > client_max_body_size;
    std::vector<std::vector<std::string> > error_page;
    std::vector<std::string> s_erorr;
    
public:
    std::vector<std::string> Vstrvalid;
    std::vector<std::vector<std::string> > servconf;
    size_t GetIndex(std::string dir);
    //________________________//
    //________loaction________//
    
    std::vector<Location> loactions;
    Location FirstFill(size_t & index);
    void FillLocation();
    


    //________________________//
    std::vector<std::string>  AddErrorPage(std::string status,std::string path);
    void desplay();
    int  checkDup(std::string der,int & index);
    bool check_isdigit(std::string str);
    void FillStatus();
    void FillValid();
    void checkValidation();
    void parceIp(std::string ip);
    int  pathExists(std::string path);
    void check_Status(std::string status);
    
    void SetPorts (); // done ~
    void SetServerName(); // done ~
    void SetHost();  // done ~
    void SetRoot();  // done ~
    void SetError_page(); // done ~
    void SetClient_max_body_size(); // done ~
    void SetIndex(); // done ~
    
    const std::vector<int> & GetPorts (); 
    const std::vector<std::string> & GetServerName(); 
    const std::vector<std::string> & GetHost();  
    const std::vector<std::string> & GetRoot();  
    const std::vector<std::vector<std::string> >&  GetError_page(); 
    const std::vector<long long int > &  GetClient_max_body_size(); 
    const std::vector<std::string> & GetIndex(); 
    
    
    void Printtwodom(const std::vector<std::vector<std::string> > & matrix,std::string data);

    template<typename T,typename V>
    void Print_dirs(T begin,T end,V data)
    {
        while(begin != end)
        {
            std::cout<<data<<"  :"<<*begin<<std::endl;
            begin++;
        }
    }



    Servers();
    ~Servers();
};


#endif