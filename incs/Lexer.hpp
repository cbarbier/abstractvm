/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:00:24 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/18 17:34:52 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
#define LEXER_HPP
#include <vector>
#include <string>

//
//
// REGEX VALUE
//      (?:(int(?:8|16|32))\((-?\d+)\)|(double|float)\((-?\d+\.\d+)\))
//
// REGEX INSTR
//      (push|pop|dump|assert|add|sub|mul|div|mod|print|exit)
//
//
//
//
//


typedef struct s_token {
    int         type;
    std::string value;
}   t_token;

class Lexer 
{
    public:
    Lexer( std::vector<std::string> & lines );
    ~Lexer();

    private:
    Lexer(const Lexer &);
    Lexer();
    Lexer &operator=(const Lexer &);

    size_t              _row;
    size_t              _col;
    const static char  *_instructions[];

};

#endif // !LEXER_HPP
