/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Analyzer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:00:24 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/19 19:49:55 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANALYZER_HPP
#define ANALYZER_HPP
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

class Analyzer
{
  public:
    typedef struct s_token
    {
        char        type;
        std::string value;
        std::string arg;
        size_t      row;

        void put(void);
    } t_token;
    typedef struct s_error
    {
        size_t row;
        size_t col;
        size_t eow;
        std::string mess;
        std::string line;

        void put(const char * name);
    } t_error;


    Analyzer(void);
    ~Analyzer();

    bool lex( std::vector<std::string> &lines );
    bool parse( void );

  private:
    bool tokenize(std::vector<std::string> &lines);
    bool parseLine(std::vector<t_token> & line);
    void chopLine(std::string &line, size_t h);
    Analyzer(const Analyzer& );
    Analyzer &operator=(const Analyzer& );

    size_t _h;
    size_t _col;
    std::vector<t_error> _errors;
    std::vector<std::vector<t_token> > _ltokens;
};

#endif // !Analyzer_HPP
