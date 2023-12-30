/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:36:57 by abouassi          #+#    #+#             */
/*   Updated: 2023/12/30 11:46:20 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParceConf.hpp"

int main(int ac , char **av)
{
    (void)ac;
    ParceConf server(av[1]);   
    // std::vector<std::vector<std::string>> matrix =  server.Vconf;
    
    // for (const auto& row : matrix) {
    //     for (std::string value : row) {
    //         std::cout << value << "|";
    //     }
    //     std::cout << std::endl;
    // }
    try
    {
        server.desplay();
        
    }
    catch(const char * e)
    {
        std::cerr << e<< '\n';
    }
    

    
}