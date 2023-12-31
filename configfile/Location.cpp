/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:23:03 by abouassi          #+#    #+#             */
/*   Updated: 2023/12/31 12:17:51 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

void Location::desplay()
{
    Printtwodom(vlocation,"location");
}
void Location::Printtwodom(const std::vector<std::vector<std::string> > & matrix,std::string data)
{
    for (std::vector<std::vector<std::string> >::const_iterator row = matrix.begin(); row != matrix.end(); ++row) {
        std::cout<<data<<"   :";
    for (std::vector<std::string>::const_iterator value = row->begin(); value != row->end(); ++value) {
        std::cout << *value << "|";
    }
    std::cout << std::endl;
}
    
}
Location::Location()
{
}

Location::~Location()
{
}
