/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParceConf.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:54:31 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/24 17:24:41 by abouassi         ###   ########.fr       */
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
    while (std::getline(ss, chunks, ' '))
    {
        if (!chunks.empty())
            vline.push_back(chunks);
    }
    return vline;
}

void ParceConf::TakeAndParce(std::string confgfile)
{
    std::ifstream configfile;
    std::string line;
    std::vector<std::string> _split;
    configfile.open(confgfile.c_str(), std::ios::in);
    if (configfile.is_open())
    {
        while (getline(configfile, line))
        {
            if (!line.empty())
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
    desplay();
}
ParceConf::ParceConf()
{

}

// Servers ParceConf::FirstFill()
// {
//     Servers server;
//     // int bracket = 0;
//     if (Vconf[index][0] != "server" || Vconf[index].size() > 1)
//     {
//         throw "Error : no server derectires";
//     }
//     else
//         server.servconf.push_back(Vconf[index]);
//     index++;

//     // if (index < Vconf.size()  && Vconf[index][0] != "{")
//     // {
//     //     throw "Error : no open brackets \n";
//     // }
//     // index++;
//     // bracket++;

//     while (index < Vconf.size() && Vconf[index][0] != "server")
//     {
//         // if (Vconf[index][0] == "{")
//         //     bracket++;

//         server.servconf.push_back(Vconf[index]);
//         index++;
//     }
//     // std::cout<<"_______br______"<<bracket<<std::endl;
//     // if (Vconf[index - 1][0] != "}")
//     // {
//     //     throw "Error : no open brackets \n";
//     // }

//     return server;
// }

Servers ParceConf::FirstFill()
{
    Servers server;
    int bracket = 0;
    if (Vconf[index][0] != "server" || Vconf[index].size() > 1)
    {
        throw "Error :'"+Vconf[index][0]+"' no server derectires ";
    }
    else
        server.servconf.push_back(Vconf[index]);
    index++;

    if (index < Vconf.size()  && Vconf[index][0] != "{")
    {
        throw "Error : no open brackets \n";
    }
    else
        server.servconf.push_back(Vconf[index]);
    index++;
    bracket++;

    while (index < Vconf.size() && bracket)
    {
        if (Vconf[index][0] == "{" )
        {
            if(Vconf[index - 1 ][0] == "location")
                bracket++;
            else
                throw "open no '"+Vconf[index][0] +"'loaction \n";
                
        }
        if (Vconf[index][0] == "}")
        {
            bracket--;
        }
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
        Vservers[i].SetAllDir();
        Vservers[i].CreatSocketServer();
        msockets[Vservers[i].server_fd] = Vservers[i];
        // cout<<"===============================================\n";
        // Vservers[i].desplay();
        // cout<<"===============================================\n";
        i++;
    }
}

ParceConf::~ParceConf()
{
}
