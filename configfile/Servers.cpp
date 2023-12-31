/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:43:44 by abouassi          #+#    #+#             */
/*   Updated: 2023/12/31 13:54:54 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Servers.hpp"

int Servers::pathExists(std::string path) {
    struct stat fileStat;
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

void Servers::Printtwodom(const std::vector<std::vector<std::string> > & matrix,std::string data)
{
    for (std::vector<std::vector<std::string> >::const_iterator row = matrix.begin(); row != matrix.end(); ++row) {
        std::cout<<data<<"   :";
    for (std::vector<std::string>::const_iterator value = row->begin(); value != row->end(); ++value) {
        std::cout << *value << "|";
    }
    std::cout << std::endl;
}
    
}

/*_____________________________________________________________*/
/*_________________________SET_________________________________*/
/*_____________________________________________________________*/

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
            throw "error invalid ip host "+ip+" \n";
        }
        len++;
    }
    if (len != 4)
        throw "error invalid ip host "+ip+" \n";

}
int Servers::checkDup(std::string der,int & index)
{
    int dup = 0;
    size_t i = 0;
    std::cout << der <<"   :"<<GetIndex("location")<<std::endl;
    while ( i < GetIndex("location"))
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
        i++;
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
        throw  ("invalid port in '" + arg + "' of the  directive \n");
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
         throw "invalid port  directive \n";
    }
    arg = servconf[i][1];

    //check hna laykon chi check
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
         throw "invalid host in  directive \n";
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
         throw "invalid root directive \n";
    }
    arg = servconf[i][1];
    if (!pathExists(arg)) 
    {
        throw ("Path '"+arg+"' does not exist.\n");
    }
    root.push_back(arg);
}
void Servers::SetIndex()
{
    int i;
    int num = checkDup("index",i);
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
       throw ("Path '"+arg+"' does not exist.\n");
    }
    index.push_back(arg);
}
void Servers::SetClient_max_body_size()
{
    int i;
    int num = checkDup("client_max_body_size",i);
    std::string arg;
    if (num == 0)
    {
        return ;
    }
    if (servconf[i].size() != 2 )
    {
         throw "invalid client_max_body_size  directive \n";
    }
    arg = servconf[i][1];
    long long int  body_size = std::strtod(arg.c_str(),NULL);
    if (!check_isdigit(arg))
    {
        throw  "invalid port in '"+ arg +"' of the  directive \n";
    }   
    client_max_body_size.push_back(body_size);
}

void Servers::check_Status(std::string status)
{
    std::vector<std::string>::iterator iter;

    iter = std::find(s_erorr.begin(),s_erorr.end(),status);
    if (iter == s_erorr.end())
    {
        throw "Error : Invalid status '"+status +"' code  Derecties\n";
    }
}
std::vector<std::string>  Servers::AddErrorPage(std::string status,std::string path)
{
    std::vector<std::string> vErrorPage;
    vErrorPage.push_back(status);
    vErrorPage.push_back(path);

    return vErrorPage;
}
void Servers::SetError_page()
{
    std::string status;
    std::string path;
    for (size_t i = 0; i < servconf.size(); i++)
    {
        if (servconf[i][0] == "error_page")
        {
            if (servconf[i].size() != 3)
            {
                throw "Error in error_page\n";
            }
            status = servconf[i][1];
            path = servconf[i][2];
            check_Status(status);
            if (!pathExists(path)) 
            {
                throw ("Path '"+path+"' does not exist.\n");
            }
            error_page.push_back(AddErrorPage(status,path));
        }
    }
    
}


/*_____________________________________________________________*/
/*_________________________GET_________________________________*/
/*_____________________________________________________________*/

const std::vector<int> & Servers::GetPorts ()
{
    return port;
}
const std::vector<std::string> & Servers::GetServerName()
{
    return server_name ;
} 
const std::vector<std::string> & Servers::GetHost()
{
    return host;
}
const std::vector<std::string> & Servers::GetRoot()
{
    return root;
}
const std::vector<std::vector<std::string> >&  Servers::GetError_page()
{
    return error_page;
}
const std::vector<long long int > &  Servers::GetClient_max_body_size()
{
    return client_max_body_size;
}
const std::vector<std::string> & Servers::GetIndex()
{
    return index;
}

/*=======================================================================*/
/*=======================================================================*/
size_t Servers::GetIndex(std::string dir)
{
    size_t i ;
    for (i = 0; i < servconf.size(); i++)
    {
        if (servconf[i][0] == dir)
        {
            return i;
        }
    }
    return (i);
}
Location Servers::FirstFill(size_t & index)
{
    Location loaction;
    loaction.vlocation.push_back(servconf[index]);
    index++;
    while (index < servconf.size() && servconf[index][0] != "location")
    {
        loaction.vlocation.push_back(servconf[index]);
        index++;
    }
    return loaction;
}


void Servers::FillLocation()
{
    size_t index = GetIndex("location");

    if (index == servconf.size())
    {
        return ;
    }
    while (index < servconf.size())
    {
        loactions.push_back(FirstFill(index));
    }
}
/*=======================================================================*/
/*=======================================================================*/

void Servers::FillStatus()
{
    s_erorr.push_back("400");
    s_erorr.push_back("401");
    s_erorr.push_back("402");
    s_erorr.push_back("403");
    s_erorr.push_back("404");
    s_erorr.push_back("405");
    s_erorr.push_back("406");
    s_erorr.push_back("407");
    s_erorr.push_back("408");
    s_erorr.push_back("409");
    s_erorr.push_back("410");
    s_erorr.push_back("411");
    s_erorr.push_back("412");
    s_erorr.push_back("413");
    s_erorr.push_back("414");
    s_erorr.push_back("415");
    s_erorr.push_back("416");
    s_erorr.push_back("417");
    s_erorr.push_back("418");
    s_erorr.push_back("421");
    s_erorr.push_back("422");
    s_erorr.push_back("423");
    s_erorr.push_back("424");
    s_erorr.push_back("425");
    s_erorr.push_back("426");
    s_erorr.push_back("428");
    s_erorr.push_back("429");
    s_erorr.push_back("431");
    s_erorr.push_back("451");
    s_erorr.push_back("500");
    s_erorr.push_back("501");
    s_erorr.push_back("502");
    s_erorr.push_back("503");
    s_erorr.push_back("504");
    s_erorr.push_back("505");
    s_erorr.push_back("506");
    s_erorr.push_back("507");
    s_erorr.push_back("508");
    s_erorr.push_back("510");
    s_erorr.push_back("511");

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
    for (size_t i = 0; i < GetIndex("location"); i++)
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
    // std::vector<std::vector<std::string> > matrix = servconf;
    
FillLocation();
Print_dirs(GetPorts().begin(),GetPorts().end(),"Pots");
Print_dirs(GetServerName().begin(),GetServerName().end(),"Server_name");
Print_dirs(GetHost().begin(),GetHost().end(),"Host");
Print_dirs(GetRoot().begin(),GetRoot().end(),"Root");
Printtwodom(GetError_page(),"Error_page");
Print_dirs(GetClient_max_body_size().begin(),GetClient_max_body_size().end(),"Client_max_body_size");
Print_dirs(GetIndex().begin(),GetIndex().end(),"Index");
size_t i = 0;
while (i < loactions.size())
{
    std::cout<<"________________________\n";
    loactions[i].desplay();
    i++;
}
   
}

Servers::Servers()
{
    
}

Servers::~Servers()
{
    
}