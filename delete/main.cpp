/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 09:51:38 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/08 14:48:11 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Delete.hpp"


int main()
{

    try
    {
        Delete delet("/nfs/homes/abouassi/Desktop/wepserv/delete/dfdf");
    }
    catch(const char * e)
    {
        std::cerr << e << '\n';
    }
}