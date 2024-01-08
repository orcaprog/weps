/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:07:22 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/08 14:48:49 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <iostream>
#include<cstring>
std::string type_d(unsigned char type)
{
    
 switch (type) {
    case DT_REG:
        return (" (Regular file)");
        break;
    case DT_DIR:
        return (" (Directory)");
        break;
    case DT_FIFO:
        return (" (Named pipe)");
        break;
    case DT_SOCK:
        return (" (Socket)");
        break;
    case DT_CHR:
        return (" (Character device)");
        break;
    case DT_BLK:
        return (" (Block device)");
        break;
    case DT_LNK:
        return (" (Symbolic link)");
        break;
    default:
        return (" (Unknown type)");
}
}

int  my_remove(std::string file)
{
    if (std::remove(file.c_str()) != 0) {
        // Print an error message if removal fails
        perror(("Error removing file  :" + file).c_str());
        return 1;
    } else {
        // Print a success message if removal is successful
        std::puts("File removed successfully");
        return 0;
    }
}
void RemoveAllPath(std::string path)
{

    int check_rm = 0;
    DIR *dir = opendir(path.c_str());
    if (dir == NULL) {
        perror("Error opening directory");
        return ;
    }
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // std::cout<<"Name :"<<entry->d_name<<std::endl;
        // std::cout<<"Type :"<<type_d(entry->d_type)<<std::endl;
        // // Check the file type 
        if (entry->d_type == DT_DIR)
        {
            RemoveAllPath(entry->d_name);
        }
        if (entry->d_type == DT_REG)
        {
            std::string filePath = std::string(path) + "/" + entry->d_name;
            check_rm += my_remove(entry->d_name);
        }
    }
    my_remove(path);
    closedir(dir);
}

int main() {
    // const char *directoryPath = "/nfs/homes/abouassi/Desktop/wepserv/delete/ex";

    RemoveAllPath("/nfs/homes/abouassi/Desktop/wepserv/delete/ex");
    // // Open the directory
    // DIR *dir = opendir(directoryPath);
    // if (dir == NULL) {
    //     perror("Error opening directory");
    //     return 1;
    // }

    // // Read and print directory entries
    // struct dirent *entry;
    // while ((entry = readdir(dir)) != NULL) {
    //     std::cout<<"Name :"<<entry->d_name<<std::endl;
    //     std::cout<<"Type :"<<type_d(entry->d_type)<<std::endl;
   
    //         std::string filePath = std::string(directoryPath) + "/" + entry->d_name;
         
    //     std::cout<<"Path :"<<filePath<<std::endl;
    //     if (std::strcmp(entry->d_name  , "." ) && std::strcmp(entry->d_name ,  "..") )
    //     {
    //         my_remove(filePath);
    //     }
    // }

    // // Close the directory
 

    return 0;
}
