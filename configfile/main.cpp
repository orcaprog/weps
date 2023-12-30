/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:36:57 by abouassi          #+#    #+#             */
/*   Updated: 2023/12/30 20:27:38 by abouassi         ###   ########.fr       */
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
    catch(std::string  e)
    {
        std::cerr << e<< '\n';
    }
    

    
}