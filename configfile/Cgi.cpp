/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:55:51 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/19 17:51:15 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cgi.hpp"


Cgi::Cgi(std::string & path,Location & location)
{
    exta = "";
    size_t pos = path.find(".");
    if ( pos == string::npos)
    {
        throw "Error in Extation form\n";
    }
    else
        exta.append(&path[pos]);
    std::string cmdCgi = location.getCmdCgi(exta);
    std::string absulpath = location.root[0] +"/" +path;
    cmds = new char *[3];
    cmds[0] =  new char[cmdCgi.length() + 1];
    strcpy(cmds[0],cmdCgi.c_str());
    cout<<"cmd :"<<cmds[0]<<endl;
    
    cmds[1] = new char[ absulpath.length() + 1];
    strcpy(cmds[1],absulpath.c_str());
    cout<<"arg :"<<cmds[1]<<endl;
    cmds[2] = NULL;
} 
void Cgi::ExecCgi()
{
    int pid = 0;
    if(pid <0){
      perror("fork fail");
      exit(1);
    }
    fd = open("out.txt",O_CREAT | O_RDWR | O_TRUNC,0644);
    std::cout<<"enter here ExecCgi \n";
    std::cout<<"fd : in cgi"<<fd<<endl;
    char * cmd;
    cmd = cmds[0];
    pid = fork();
    if (pid == 0)
    {
        dup2(fd, STDOUT_FILENO);
        if(execve(cmd,cmds,NULL) == -1)
        {
            std::cout<<"No exec\n";
            perror("execve");
            exit(1);
            
        }
    }
    waitpid(pid,NULL,0);
    close(fd);
}

Cgi::~Cgi()
{
    for (size_t i=0; i < 3 ; i++)
		delete [] cmds[i];

	delete [] cmds;
}
