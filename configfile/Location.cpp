/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:23:03 by abouassi          #+#    #+#             */
/*   Updated: 2023/12/31 18:57:41 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"


void Location::FillValid()
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
void Location::checkValidation()
{
    std::vector<std::string>::iterator iter;
    for (size_t i = 0; i < vlocation.size() ; i++)
    {
        iter = std::find(Vstrvalid.begin(),Vstrvalid.end(),vlocation[i][0]);
        if (iter == Vstrvalid.end())
        {
            throw "Error : Invalid Derecties\n";
        }
    }
    
}



int Location::pathExists(std::string path) {
    struct stat fileStat;
    return stat(path.c_str(), &fileStat) == 0;
}
size_t Location::GetIndex(std::string dir)
{
    size_t i ;
    for (i = 0; i < vlocation.size(); i++)
    {
        if (vlocation[i][0] == dir)
        {
            return i;
        }
    }
    return (i);
}
int Location::checkDup(std::string der,int & index)
{
    int dup = 0;
    size_t i = 0;
    while ( i < vlocation.size())
    {
        if (vlocation[i][0] == der)
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
void Location::desplayLocation()
{
    FillValid();
    checkValidation();
    
    SetRoot();
    SetAllowMethods();
    SetUpload();
    SetCgiPath();
    SetAutoindex();
    SetPath();
    Printtwodom(vlocation,"location");
}
void Location::Printtwodom(const std::vector<std::vector<std::string> > & matrix,std::string data)
{
    std::cout<<data<<"   :\n";
    for (std::vector<std::vector<std::string> >::const_iterator row = matrix.begin(); row != matrix.end(); ++row) {
        
    for (std::vector<std::string>::const_iterator value = row->begin(); value != row->end(); ++value) {
        std::cout <<"   :"<< *value << "|";
    }
    std::cout << std::endl;
    } 
}

void Location::parce_location()
{
    
}

void Location::SetRoot()
{
    int i;
    int num = checkDup("root",i);
    std::string arg;
    if (num == 0)
    {
        return ;
    }
    if (vlocation[i].size() != 2 )
    {
         throw "invalid root directive \n";
    }
    arg = vlocation[i][1];
    if (!pathExists(arg)) 
    {
        throw ("Path '"+arg+"' does not exist.\n");
    }
    root.push_back(arg);
}
void Location::SetPath()
{
    int i;
    int num = checkDup("location",i);
    std::string arg;
    if (num == 0)
    {
        return ;
    }
    if (vlocation[i].size() != 2 )
    {
         throw "invalid location directive \n";
    }
    arg = vlocation[i][1];
    // if (!pathExists(arg))
    // {
    //     throw ("Path '"+arg+"' does not exist.\n");
    // }
    path.push_back(arg);
}
void Location::CheckMethods(std::string methd)
{
    std::vector<std::string> allMethds;
    std::vector<std::string>::iterator iter;
    allMethds.push_back("POST");
    allMethds.push_back("GET");
    allMethds.push_back("DELETE");
    iter = std::find(allMethds.begin(),allMethds.end(),methd);
    if (iter == allMethds.end())
    {
        throw "error no method "+methd+ " exists\n";
    } 
}
void Location::SetAllowMethods()
{
    int i;
    int num = checkDup("allow_methods",i);
    std::string arg;
    std::vector<std::string> vallow;
    if (num == 0)
    {
        return ;
    }
    if (vlocation[i].size() > 4 || vlocation[i].size() < 2 )
    {
         throw "invalid methods arguments directive \n";
    }
    vallow =  vlocation[i];

    
    std::vector<std::string>::iterator iter;
    iter = vallow.begin();
    iter++;
    while (iter != vallow.end())
    {
        CheckMethods(*iter);
        allow_methods.push_back(*iter);
        iter++;
    }    
}
void Location::SetAutoindex()
{
    int i;
    int num = checkDup("autoindex",i);
    std::string arg;
    if (num == 0)
    {
        return ;
    }
    if (vlocation[i].size() != 2 )
    {
         throw "invalid autoindex directive \n";
    }
    arg = vlocation[i][1];
    if (arg != "on" &&  arg != "off")
    {
        throw "The argument  '"+arg+ "' is not valid\n";
    }
    if (arg == "on ")
        autoindex = 1;
    else
        autoindex = 0;
}
void Location::SetUpload()
{
    int i;
    int num = checkDup("upload",i);
    std::string arg;
    if (num == 0)
    {
        return ;
    }
    if (vlocation[i].size() != 2 )
    {
         throw "invalid upload directive \n";
    }
    arg = vlocation[i][1];
    if (arg != "on" &&  arg != "off")
    {
        throw "The argument  '"+arg+ "' is not valid\n";
    }
    if (arg == "on ")
        upload = 1;
    else
        upload = 0;
}







// void Location::check_Status(std::string status)
// {
//     std::vector<std::string>::iterator iter;

//     iter = std::find(s_erorr.begin(),s_erorr.end(),status);
//     if (iter == s_erorr.end())
//     {
//         throw "Error : Invalid status '"+status +"' code  Derecties\n";
//     }
// }

std::vector<std::string>  Location::AddcgiPaths(std::string status,std::string path)
{
    std::vector<std::string> vErrorPage;
    vErrorPage.push_back(status);
    vErrorPage.push_back(path);

    return vErrorPage;
}
void Location::SetCgiPath()
{
    std::string extantion;
    std::string path;
    for (size_t i = 0; i < vlocation.size(); i++)
    {
        if (vlocation[i][0] == "cgi_path")
        {
            if (vlocation[i].size() != 3)
            {
                throw "Error in error_page\n";
            }
            extantion = vlocation[i][1];
            path = vlocation[i][2];
            // check_extantion(extantion);
            if (!pathExists(path)) 
            {
                throw ("Path '"+path+"' does not exist.\n");
            }
            cgi_path.push_back(AddcgiPaths(extantion,path));
        }
    }
    
}



/*__________________________________________*/
/*__________________________________________*/
/*__________________________________________*/

const std::vector<std::string> & Location::GetPath()
{
    return path;
}
const std::vector<std::string> & Location::GetAllowMethods()
{
    return allow_methods;
}
const bool & Location::GetAutoindex()
{
    return autoindex;
}
const bool & Location::GetUpload()
{
    return upload;
}
const std::vector< std::vector<std::string> > & Location::GetCgiPath()
{
    return cgi_path;
}
const std::vector<std::string> & Location::GetRoot()
{
    return root;
}

Location::Location()
{
}

Location::~Location()
{
}
