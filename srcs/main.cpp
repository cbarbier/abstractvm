/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 14:14:05 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/18 15:05:35 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AbstractVM.hpp>
#include <Lexer.hpp>
#include <iostream>

int         main( int argc, char **argv)
{
    // std::cout << "abstract vm in progress" << std::endl;

    if (argc > 2)
    {
        std::cerr << "Usage: ./abstractVM [filename]" << std::endl;
    }
    AbstractVM vm( argc == 2 ? argv[1] : 0);
    Lexer      lexer(vm.getLines());




    return (0);
}
