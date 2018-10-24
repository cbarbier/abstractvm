/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:51:53 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/24 09:05:15 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AbstractVM.hpp>
#include <Utils.hpp>
#include <iostream>
#include <fstream>

AbstractVM::AbstractVM(char *pfile) : _pfile(pfile)
{
    if (!pfile)
    {
        this->getInput(std::cin);
        return;
    }
    std::ifstream file;
    std::ios_base::iostate state = file.exceptions();
    file.exceptions( std::ifstream::badbit | std::ifstream::failbit ); //catch (const std::ifstream::failure& e)
    
    try{
        file.open(pfile);
    }
    catch (const std::ifstream::failure & e){
        std::cerr << "Error: opening / reading the file [" << pfile << "]" << std::endl;
        std::exit(1);
    }
    file.exceptions(state);
    this->getInput(file);
}

void AbstractVM::getInput(std::istream &is)
{
    std::string line;

    while (!is.fail() && !is.eof())
    {
        std::getline(is, line, '\n');
        // std::cout << "line: " << line << std::endl;
        // line = Utils::trim(line);
        if (line == ";;" && !this->_pfile)
            break;
        line = Utils::rmComment(line);
        // if (line.length())
        this->_lines.push_back(line);
    }
}

std::vector<std::string> &AbstractVM::getLines(void)
{
    return this->_lines;
}

AbstractVM::~AbstractVM()
{
}

const char* AbstractVM::MyException::what() const throw()
{
    return "myException test";
}
const char* AbstractVM::Underflow::what() const throw()
{
    return "Underflow";
}
const char* AbstractVM::Overflow::what() const throw()
{
    return "Overflow";
}
const char* AbstractVM::DivByZero::what() const throw()
{
    return "Division by zero";
}
const char* AbstractVM::ModByZero::what() const throw()
{
    return "Modulo by zero";
}
