/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:49:58 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/08 16:48:07 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETE_HPP
#define DELETE_HPP

#include <stdio.h>
#include <dirent.h>
#include <iostream>
#include<cstring>

#include "../configfile/ParceConf.hpp"
class Delete
{

public:
    Delete(std::string path);

    int  my_remove(std::string file);
    void RemoveAllPath(std::string path);
    int pathExists(std::string path);

    ~Delete();
};
#endif