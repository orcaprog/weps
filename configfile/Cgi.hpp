/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:53:23 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/17 15:56:08 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include "Servers.hpp"
#include "Location.hpp"
using namespace std;
class Cgi
{
private:
    /* data */
public:
    Cgi(std::string path ,Location location);
    ~Cgi();
};




#endif