/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Analyzer.cpp                                       :+:      :+:    :+:   */
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
    std::regex re_instr("(push|pop|dump|assert|add|sub|mul|div|mod|print|exit|and|or|xor)");
    std::regex re_value("(?:(int(?:8|16|32))\\((.*)\\)|(double|float)\\((.*)\\))");

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
        token.row = h;
        error.col = pos;
        error.eow = end;

        if (std::regex_match(word, sm, re_instr))
        {
            token.type = 'I'; //for instruction
            token.value = std::string(sm[0]);
            vtoken.push_back(token);
        }
        else if (std::regex_search(word, sm, re_instr))
        {
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
            // std::cout << "not a valid token" << std::endl;
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
        return true;
    }
    //print the lexer errors;
    std::vector<t_error>::iterator it = this->_errors.begin(), ite = this->_errors.end();
    for (; it != ite; ++it)
        it->put("Lexer");
    return false;
}

bool Analyzer::parse( std::vector<std::string> &lines )
{
    std::vector<std::vector<t_token> >::iterator it = this->_ltokens.begin(), ite = this->_ltokens.end();
    for (; it != ite; ++it)
    {
      this->parseLine(*it, lines);
    }
    // print parse errors
    bool ret = true;
    if (this->_errors.size())
    {
        std::vector<t_error>::iterator iterr = this->_errors.begin(), iterre = this->_errors.end();
        for (; iterr != iterre; ++iterr)
            iterr->put("Parser");
        ret = false;
    }
    if (!this->_vexit.size())
    {
        std::cerr << "\x1b[31mError: \x1b[32mParser: \x1b[35mthere must be an EXIT instruction in the program\x1b[0m" << std::endl;
        return false;
    }
    if (this->_vexit.size() > 1)
    {
        std::vector<int>::iterator it_vexit = this->_vexit.begin(), ite_vexit = this->_vexit.end();
        std::cerr << "\x1b[31mError: \x1b[32mParser: \x1b[35mthere is more than one  EXIT instruction in the program :\x1b[0m" << std::endl;
        for (; it_vexit != ite_vexit; ++it_vexit)
            std::cerr << "line " << (*it_vexit + 1)  << std::endl;
        std::cerr << "\x1b[0m";
        return false;
    }
    return ret;
}

bool Analyzer::parseLine(std::vector<t_token> & line, std::vector<std::string> & original_lines)
{
    t_error     err;

    if (!line.size())
        return true;
    err.row = line.at(0).row;
    err.col = 0;
    err.line = original_lines.at(err.row);
    if (line.at(0).value == "exit")
    {
        this->_vexit.push_back(err.row);
    }
    if (line.size() > 2)
    {
        err.mess = std::string("too many tokens on the same line");
        this->_errors.push_back(err);
        return false;
    }
    if (line.at(0).type != 'I')
    {
        err.mess = std::string("expecting an instruction like [pop push assert add sub ...]");
        this->_errors.push_back(err);
        return false;
    }
    if (line.size() == 1 && ( line.at(0).value == "push" || line.at(0).value == "assert" ) )
    {
        err.mess = std::string("expecting a value like [int32() double() float() ...]");
        this->_errors.push_back(err);
        return false;
    }
    if (line.size() == 2 && line.at(0).value != "push" && line.at(0).value != "assert")
    {
        err.mess = std::string("expecting an ENDL after this instruction \x1b[32m") + line.at(0).value + std::string("\x1b[0m"); 
        this->_errors.push_back(err);
        return false;
    }
    if (line.size() == 2 && ( line.at(0).value == "push" || line.at(0).value == "assert" ) )
    {
        if (line.at(1).type != 'V')
        {
            err.mess = std::string("execting a VALUE [int32() double()] after this instruction \x1b[32m") + line.at(0).value + std::string("\x1b[0m"); 
            this->_errors.push_back(err);
            return false;
        }
        std::string val = line.at(1).arg;
        std::smatch sm;
        std::regex re_N("(-?\\d*)");
        std::regex re_Z("(-?\\d*\\.\\d*)");

        if (line.at(1).value == "double" || line.at(1).value == "float")
        {
            if (std::regex_match(val, sm, re_Z))
                return true;
            err.mess = std::string("expecting a value matching /-?[0-9]+.[0-9]+/");
            this->_errors.push_back(err);
            return false;
        } else {
             if (std::regex_match(val, sm, re_N))
                return true;
            err.mess = std::string("expecting a value matching /-?[0-9]+/");
            this->_errors.push_back(err);
            return false;
        }
        return false;
    }
    return true;
}

void Analyzer::put_tokens( void )
{
    if (!DEBUG)
        return;
    std::vector<std::vector<t_token> >::iterator it = this->_ltokens.begin(), ite = this->_ltokens.end();
    for (;it != ite; ++it)
    {
        std::cerr << "<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
        std::vector<t_token>::iterator itt = it->begin(), itte = it->end();
        for (;itt != itte; ++itt)
            itt->put();
        std::cerr << ">>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    }
}

std::vector<std::vector<Analyzer::t_token> > &Analyzer::getTokens( void )
{
    return this->_ltokens;
}


void Analyzer::t_error::put( const char * name )
{
    if (this->eow > this->line.length())
        this->eow = 0;
    std::cerr << std::endl
              << "> " << this->line.substr(0, this->col) << "\x1b[35m" << this->line.substr(this->col, this->eow - this->col) << "\x1b[0m" << this->line.substr(this->eow);
    std::cerr << std::endl << "\x1b[31mError: \x1b[32m" << name << "\x1b[0m: [" << this->row << ":" << this->col << "] \x1b[35m" << this->mess << "\x1b[0m" << std::endl;
}

void Analyzer::t_token::put(void) const
{
    std::cerr << "{" << std::endl << "\
    type: " << this->type << std::endl << "\
    value: " << this->value << std::endl << "\
    arg: " << this->arg << std::endl << "\
    row: " << this->row << std::endl << "\
    }" << std::endl; 
}
