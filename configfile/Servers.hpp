/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:42:27 by abouassi          #+#    #+#             */
/*   Updated: 2023/12/29 20:08:10 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERS_HPP
#define SERVERS_HPP
#include <vector>
#include <iostream>
#include <algorithm> 
class Servers
{
private:
    
public:
    std::vector<std::string> Vstrvalid;
    std::vector<std::vector<std::string>> servconf;
    std::vector<int> port;
    void desplay();

    void FillValid();
    void checkValidation();
    void SetPorts ();
    
    Servers();
    ~Servers();
};


#endif