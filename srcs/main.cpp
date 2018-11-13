/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 14:14:05 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/24 09:08:50 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AbstractVM.hpp>
#include <Analyzer.hpp>
#include <iostream>

int         main( int argc, char **argv)
{
    // std::cout << "abstract vm in progress" << std::endl;
    // std::cout << std::numeric_limits<int8_t>::max() << std::endl;
    // std::cout << std::numeric_limits<int16_t>::max() << std::endl;
    // std::cout << std::numeric_limits<double>::max() << std::endl;
    // std::cout << std::numeric_limits<long double>::max() << std::endl;
    // std::cout << std::numeric_limits<double>::min() << std::endl;
    if ( argc > 2 )
    {
        std::cerr << "Usage: ./abstractVM [filename]" << std::endl;
        return( 1 );
    }
    AbstractVM vm( argc == 2 ? argv[1] : 0);
    Analyzer      analyzer;
    std::vector<std::string> & lines = vm.getLines();
    if (!analyzer.lex( lines )) // LEXER TOKENIZING THE ENTIRE PROGRAM 
        return (1);
    if (!analyzer.parse( lines )) // PARSER CHECKING THE SYNTAX OF THE ENTIRE PROGRAM
        return (1);
    analyzer.put_tokens();
    vm.exec(analyzer.getTokens());
   
    return (0);
}
