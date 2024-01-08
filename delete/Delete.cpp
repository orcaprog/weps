/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 09:43:27 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/08 09:51:27 by abouassi         ###   ########.fr       */
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

Delete::~Delete()
{
}