/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 09:43:27 by abouassi          #+#    #+#             */
/*   Updated: 2024/02/01 09:28:00 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Delete.hpp"

int Delete::pathExists(std::string path) {
    struct stat fileStat;
    return stat(path.c_str(), &fileStat) == 0;
}

Delete::Delete(std::string path,std::string rootPath)
{
    if (realpath(rootPath.c_str(),path.data()) == NULL)
    {
        throw "Delete Error: path not exist \n";
    }
    RemoveAllPath(path);
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
    // struct stat stat_info;
    std::string path_plus;
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
                path_plus = path + "/"+entry->d_name;
                // stat(path_plus.c_str(),&stat_info);
                // if (stat_info.st_mode & S_IWOTH)
                // {
                // }
                
                RemoveAllPath(path_plus);
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