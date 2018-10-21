/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Analyzer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:04:26 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/19 20:04:56 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Analyzer.hpp>
#include <AbstractVM.hpp>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <regex>

Analyzer::Analyzer(void) {}
Analyzer::~Analyzer(void) {}

void Analyzer::chopLine(std::string &line, size_t h)
{
    size_t pos = line.find_first_not_of(" \t");
    size_t end;
    std::string word;
    std::vector<t_token> vtoken;
    std::smatch sm;
    std::regex re_instr("(push|pop|dump|assert|add|sub|mul|div|mod|print|exit)");
    std::regex re_value("(?:(int(?:8|16|32))\\((.*)\\)|(double|float)\\((.*)\\))");
    // std::regex re_N("(-?\d*)");
    // std::regex re_Z("(-?\d*\.\d*)");

    // std::replace(line.begin(), line.end(), '\t', ' ');
    // ss << line;
    std::cout << "h: " << h << std::endl;
    t_error error;
    error.line = line;

    t_token token;
    while (pos != std::string::npos)
    {
        end = line.find_first_of(" \t", pos);
        if (end == std::string::npos)
            end = line.length();
        word = line.substr(pos, end - pos);
        error.row = h;
        error.col = pos;
        error.eow = end;
        std::cout << "[" << word << "]" << std::endl;

        if (std::regex_match(word, sm, re_instr))
        {
            // std::cout << "instr perfect match" << sm.size() << std::endl;
            token.type = 'I'; //for instruction
            token.value = std::string(sm[0]);
            vtoken.push_back(token);
        }
        else if (std::regex_search(word, sm, re_instr))
        {
            // std::cout << "instr search but not match" << sm.size() << std::endl;
            error.mess = std::string(std::string("did you mean \x1b[32m") + std::string(sm[0]) + std::string("\x1b[0m"));
            this->_errors.push_back(error);
        }
        else if (std::regex_match(word, sm, re_value))
        {
            // std::cout << "value perfect match" << sm.size() << std::endl;
            token.type = 'V';
            token.value = std::string(sm[sm[1].length() ? 1 : 3]);
            token.arg = std::string(sm[sm[1].length() ? 2 : 4]);
            vtoken.push_back(token);
        }
        else if (std::regex_search(word, sm, re_value))
        {
            // std::cout << "value search but not match" << sm.size() << std::endl;
            error.mess = std::string(std::string("did you mean \x1b[32m") + std::string(sm[0]) + std::string("\x1b[0m"));
            this->_errors.push_back(error);
        }
        else
        {
            error.mess = std::string("Unknown token");
            this->_errors.push_back(error);
            std::cout << "not a valid token" << std::endl;
        }
        if (end == std::string::npos)
            break;
        pos = line.find_first_not_of("\t ", end);
    }
    this->_ltokens.push_back(vtoken);
}

bool Analyzer::tokenize(std::vector<std::string> &lines)
{
    size_t h = 0;
    std::vector<std::string>::iterator it = lines.begin(), ite = lines.end();
    std::string line;
    for (; it != ite; ++it)
    {
        line = *it;
        if (line.length())
        {
            this->chopLine(line, h);
        }
        h++;
    }
    return true;
}

bool Analyzer::lex(std::vector<std::string> &lines)
{
    this->_h = lines.size();

    this->tokenize(lines);

    if (!this->_errors.size())
    {
        //DEBUG for TOKENS vector;
        // std::vector<std::vector<t_token> >::iterator it = this->_ltokens.begin(), ite = this->_ltokens.end();
        // for (; it != ite; ++it)
        // {
        //     std::cout << "NEW LINE" << std::endl;
        //     std::vector<t_token>::iterator itt = it->begin(), itet = it->end();
        //     for (; itt != itet; ++itt)
        //     {
        //         itt->put();
        //     }
        //     std::cout << "END OF LINE" << std::endl;
        // }
        return true;
    }
    //print the errors;
    std::vector<t_error>::iterator it = this->_errors.begin(), ite = this->_errors.end();
    for (; it != ite; ++it)
        it->put();
    return false;
}

bool Analyzer::parse(std::vector<std::string> &lines)
{
    (void)lines;
    return true;
}

void Analyzer::t_error::put(void)
{
    std::cerr << std::endl
              << "> " << this->line.substr(0, this->col) << "\x1b[35m" << this->line.substr(this->col, this->eow - this->col) << "\x1b[0m" << this->line.substr(this->eow) << std::endl;
    std::cerr << "Error: Analyzer: [" << this->row << ":" << this->col << "] " << this->mess << std::endl;
}

void Analyzer::t_token::put(void)
{
    std::cout << "{ \n\
    type: " << this->type << std::endl << "\
    value: " << this->value << std::endl << "\
    arg: " << this->arg << std::endl << "\
    }" << std::endl; 
}
