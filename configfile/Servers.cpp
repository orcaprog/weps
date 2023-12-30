/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:43:44 by abouassi          #+#    #+#             */
/*   Updated: 2023/12/30 12:38:27 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Servers.hpp"

int Servers::pathExists(std::string path) {
    struct stat fileStat;
        std::cout<<"____error____\n"; 
    return stat(path.c_str(), &fileStat) == 0;
}

bool Servers::check_isdigit(std::string str)
{
    int i = 0;
    while (str[i])
    {
        if (!isdigit(str[i]))
        {
            return (0);
        }
        i++;
    }
    return (1);
}


void Servers::parceIp(std::string ip)
{
    std::stringstream ss;
    ss << ip;
    std::string line;
    int net = 0;
    int len = 0;
    while (getline(ss,line,'.'))
    {
        net = std::atoi(line.c_str()) ;
        if (line.size() > 3 || !check_isdigit(line) || net > 255 || net < 0)
        {
            throw "error invalid ip host1\n";
        }
        len++;
    }
    if (len != 4)
        throw "error invalid ip host\n";

}
int Servers::checkDup(std::string der,int & index)
{
    int dup = 0;
    for (size_t i = 0; i < servconf.size(); i++)
    {
        if (servconf[i][0] == der)
        {
            index = i;
            dup++;
        }
        if (dup > 1)
        {
           throw "Error duplicate derective \n";
        }
        
    }
    return (dup);
}
void Servers::SetPorts ()
{
    int i;
    int num = checkDup("listen",i);
    std::string arg;
    if (num == 0)
    {
        return ;
    }
    if (servconf[i].size() != 2 )
    {
         throw "invalid port in of the listen directive \n";
    }
    arg = servconf[i][1];
    int myport = std::atoi(arg.c_str());
    if (!check_isdigit(arg)  || myport > 65535)
    {
        throw  ("invalid port in " + arg + "of the  directive \n");
    }
    port.push_back(myport);
}

void Servers::SetServerName()
{
    int i;
    int num = checkDup("server_name",i);
    std::string arg;
    if (num == 0)
    {
        return ;
    }
    if (servconf[i].size() != 2 )
    {
         throw "invalid port in of the server_name directive \n";
    }
    arg = servconf[i][1];
    server_name.push_back(arg);
}


void Servers::SetHost()
{
    int i;
    int num = checkDup("host",i);
    std::string arg;
    if (num == 0)
    {
        return ;
    }
    if (servconf[i].size() != 2 )
    {
         throw "invalid port in of the server_name directive \n";
    }
    arg = servconf[i][1];
    parceIp(arg);
    
    host.push_back(arg);
}
void Servers::SetRoot()
{
    int i;
    int num = checkDup("root",i);
    std::string arg;
    if (num == 0)
    {
        return ;
    }
    if (servconf[i].size() != 2 )
    {
         throw "invalid port in of the server_name directive \n";
    }
    arg = servconf[i][1];
    if (!pathExists(arg)) 
    {
        throw ("Path does not exist.\n");
    }
    root.push_back(arg);
}
void Servers::FillValid()
{
     Vstrvalid.push_back("listen");
     Vstrvalid.push_back("server");
     Vstrvalid.push_back("server_name");
     Vstrvalid.push_back("host");
     Vstrvalid.push_back("root");
     Vstrvalid.push_back("error_page");
     Vstrvalid.push_back("client_max_body_size");
     Vstrvalid.push_back("index");
     Vstrvalid.push_back("location");
     Vstrvalid.push_back("{");
     Vstrvalid.push_back("}");
     Vstrvalid.push_back("#");
     Vstrvalid.push_back("allow_methods");
     Vstrvalid.push_back("autoindex");
     Vstrvalid.push_back("upload");
     Vstrvalid.push_back("cgi_path");
}
void Servers::checkValidation()
{
    std::vector<std::string>::iterator iter;
    for (size_t i = 0; i < servconf.size(); i++)
    {
        iter = std::find(Vstrvalid.begin(),Vstrvalid.end(),servconf[i][0]);
        if (iter == Vstrvalid.end())
        {
            throw "Error : Invalid Derecties\n";
        }
    }
    
}
void Servers::desplay()
{
    std::vector<std::vector<std::string> > matrix = servconf;
    for (std::vector<std::vector<std::string> >::const_iterator row = matrix.begin(); row != matrix.end(); ++row) {
        for (std::vector<std::string>::const_iterator value = row->begin(); value != row->end(); ++value) {
            std::cout << *value << "|";
        }
        std::cout << std::endl;
    }
}

Servers::Servers()
{
    
}

Servers::~Servers()
{
    
}