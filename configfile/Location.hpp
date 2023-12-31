/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:23:05 by abouassi          #+#    #+#             */
/*   Updated: 2023/12/31 11:57:32 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP


#include <algorithm> 
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <map>
#include <sys/stat.h>
class Location
{
private:



public:
    void Printtwodom(const std::vector<std::vector<std::string> > & matrix,std::string data);
    void desplay();
    std::vector<std::vector<std::string> > vlocation;
    Location();
    ~Location();
};





#endif