/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParceConf.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:54:35 by abouassi          #+#    #+#             */
/*   Updated: 2023/12/29 16:53:20 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCECONF_HPP
#define PARCECONF_HPP
#include <iostream>
#include <fstream>
#include "Servers.hpp"
#include <sstream>
#include <vector>
#include <deque>
#include <map>
class ParceConf
{
private:
int index;
public:
    std::vector< Servers > Vservers;
    std::vector<std::vector<std::string>>  Vconf;
    // std::vector<std::pair<int,std::vector<std::string>>>  Vconf;
    Servers FirstFill();
    std::vector<std::string> Split_line(std::string line);

    void FillServers();
    void desplay();
    ParceConf(std::string confgfile);
    ~ParceConf();
};




#endif