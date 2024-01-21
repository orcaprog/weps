/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:53:23 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/19 10:01:41 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include "Servers.hpp"
#include "Location.hpp"

#include <iostream>
   #include <sys/types.h>
       #include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>

using namespace std;
class Cgi
{
string exta;
char **cmds;
std::string const *command[2];
public:
    
    int fd;
    string findCgiPath(Location & location , string & path);
    void ExecCgi();
    Cgi(std::string & path,Location & location);
    ~Cgi();
};




#endif