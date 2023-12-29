/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:43:44 by abouassi          #+#    #+#             */
/*   Updated: 2023/12/29 20:16:21 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Servers.hpp"

void Servers::SetPorts ()
{
   
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
    std::vector<std::vector<std::string>> matrix = servconf;
    for (const auto& row : matrix) {
        for (std::string value : row) {
            std::cout << value << "|";
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