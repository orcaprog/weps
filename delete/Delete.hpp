/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 09:43:30 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/08 09:50:27 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETE_HPP
#define DELETE_HPP

#include "../configfile/ParceConf.hpp"
class Delete
{
private:
    /* data */
public:
    Delete(std::string path);
    int pathExists(std::string path);

    ~Delete();
};
#endif