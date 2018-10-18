/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:04:26 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/18 17:06:37 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Lexer.hpp>
#include <AbstractVM.hpp>
#include <iostream>

const char      *Lexer::_instructions[] = {"push", "pop", "dump", "assert", "add", "sub", "mul", "div", "mod", "print", "exit"};

Lexer::Lexer( std::vector<std::string> & lines )
{
    std::vector<std::string>::iterator it=lines.begin(), ite = lines.end();
    for(;it!=ite;++it)
        std::cout << *it << std::endl;    
}

Lexer::~Lexer( void )
{

}

