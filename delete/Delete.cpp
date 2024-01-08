/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 09:43:27 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/08 16:28:39 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Delete.hpp"

int Delete::pathExists(std::string path) {
    struct stat fileStat;
    return stat(path.c_str(), &fileStat) == 0;
}


Delete::Delete(std::string path)
{
    if (!pathExists(path))
    {
        throw "Delete Error: path not exist \n";
    }
    
}

int  Delete::my_remove(std::string file)
{
    if (std::remove(file.c_str()) != 0) 
    {
        perror(("Error removing file  :" + file).c_str());
        return 1;
    } 
    else 
    {
        std::puts(("File removed successfully:" + file).c_str());
        return 0;
    }
}

void Delete::RemoveAllPath(std::string path)
{

    int check_rm = 0;
    std::cout<<"path   :"<<path<<std::endl;
    DIR *dir = opendir(path.c_str());
    if (dir == NULL) {
        perror("Error opening directory");
        return ;
    }
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR)
        {

            if (std::strcmp(entry->d_name  , ".") && std::strcmp(entry->d_name ,"..") )
            {
                RemoveAllPath(path + "/"+entry->d_name);
                std::cout<<"dir :"<<entry->d_name<<std::endl;
                
            }
        }
        else
        {
            std::string filePath = std::string(path) + "/" + entry->d_name;
            std::cout<<"file :"<<filePath<<std::endl;
            check_rm += my_remove(filePath );
        }
    }
    closedir(dir);
    my_remove(path);
}


Delete::~Delete()
{
}