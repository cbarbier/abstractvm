/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:00:24 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/19 19:49:55 by cbarbier         ###   ########.fr       */
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

class Lexer
{
  public:
    typedef struct s_token
    {
        char        type;
        std::string value;
        std::string arg;

        void put(void);
    } t_token;
    typedef struct s_error
    {
        size_t row;
        size_t col;
        size_t eow;
        std::string mess;
        std::string line;

        void put(void);
    } t_error;


    Lexer(void);
    ~Lexer();

    bool tokenize(std::vector<std::string> &lines);
    bool run(std::vector<std::string> &lines);

  private:
    void chopLine(std::string &line, size_t h);
    Lexer(const Lexer &);
    Lexer &operator=(const Lexer &);

    size_t _h;
    size_t _col;
    std::vector<t_error> _errors;
    std::vector<std::vector<t_token> > _ltokens;
};

#endif // !LEXER_HPP
