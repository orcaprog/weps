/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParceConf.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:54:31 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/02 18:17:31 by abouassi         ###   ########.fr       */
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
    while (std::getline(ss,chunks,' '))
    {
        if(!chunks.empty())
            vline.push_back(chunks);
    }
    return vline;
}

ParceConf::ParceConf(std::string confgfile)
{
    std::ifstream configfile;
    std::string line;
    std::vector<std::string> _split;
    configfile.open(confgfile.c_str(), std::ios::in);
    if (configfile.is_open()) 
    {
        while (getline(configfile, line)) {
            
            if (!line.empty() )
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
}

Servers ParceConf::FirstFill()
{
    Servers server;
    // int bracket = 0;
    if (Vconf[index][0] != "server" || Vconf[index].size() > 1)
    {
        throw "Error : no server derectires";
    }
    else
        server.servconf.push_back(Vconf[index]);
    index++;
    
    // if (index < Vconf.size()  && Vconf[index][0] != "{")
    // {
    //     throw "Error : no open brackets \n";
    // }
    // index++;
    // bracket++;
    
    while (index < Vconf.size() && Vconf[index][0] != "server")
    {
        // if (Vconf[index][0] == "{")
        //     bracket++;

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

    // if(Vconf[0][0] != "server")
    // {
    //     throw "Error : no server derectires";
    // }
    // for (size_t i = 0; i < Vconf.size(); i++)
    // {
        
    //     Vcol = Vconf[i];
    //     Vservers[x].vconf.push_back(Vcol);
    // }
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
        std::cout<<"###############################"<<std::endl;
        
        Vservers[i].SetAllDir();
        Vservers[i].desplay();
        std::cout<<"###############################"<<std::endl;
        i++;
    }
    // std::vector<std::vector<std::string>> matrix =  Vservers[0].vconf;
    // for (const auto& row : matrix) {
    //     for (std::string value : row) {
    //         std::cout << value << "|";
    //     }
    //     std::cout << std::endl;
    // }
}
// void ParceConf::CreatSocketServer()
// {
    
// }
ParceConf::~ParceConf()
{
}

//  Vconf.push_back(std::pair<int, std::vector<std::string>>(0, Split_line(line)));
//      std::vector<std::pair<int,std::vector<std::string>>>  matrix =  Vconf;
//     std::cout<<"jdjdfjfj\n";
//     for (const auto& row : matrix) {
//         std::cout<<"key  :"<<row.first<<"  ";
//         for (std::string value : row.second) {
//             std::cout << value << "|";
//         }
//         std::cout << std::endl;
//     }