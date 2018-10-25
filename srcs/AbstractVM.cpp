/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:51:53 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/25 09:30:33 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AbstractVM.hpp>
#include <Utils.hpp>
#include <iostream>
#include <fstream>


t_instr         AbstractVM::_instructions[] = {
        { "push", 1, &AbstractVM::instr_push },
        { "pop", 0, &AbstractVM::instr_pop },
        { "dump", 0, &AbstractVM::instr_dump },
        { "assert", 1, &AbstractVM::instr_assert },
        { "add", 0, &AbstractVM::instr_add },
        { "sub", 0, &AbstractVM::instr_sub },
        { "mul", 0, &AbstractVM::instr_mul },
        { "div", 0, &AbstractVM::instr_div },
        { "mod", 0, &AbstractVM::instr_mod },
        { "print", 0, &AbstractVM::instr_print },
        { "exit", 0, &AbstractVM::instr_exit },
        { "", 0, 0 }
    };

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

void        AbstractVM::instr_push( void )
{

}

void        AbstractVM::instr_pop( void )
{
    if (this->_deque.size() < 2)
        throw AbstractVM::PopOnEmptyStack();
}

void        AbstractVM::instr_dump( void )
{
    std::deque<IOperand *>::iterator        it = this->_deque.begin();
    std::deque<IOperand *>::iterator        ite = this->_deque.end();

    for(;it != ite; ++it)
        std::cout << (*it)->toString << std::endl;
}

void        AbstractVM::instr_assert( void )
{
}

void        AbstractVM::instr_add( void )
{
    if ( this->_deque.size() < 2 )


}

void        AbstractVM::instr_sub( void )
{

}

void        AbstractVM::instr_mul( void )
{

}

void        AbstractVM::instr_div( void )
{

}

void        AbstractVM::instr_mod( void )
{

}

void        AbstractVM::instr_print( void )
{

}

void        AbstractVM::instr_exit( void )
{

}

void        AbstractVM::exec( std::vector<std::vector<t_token> > &tokens )
{
    Utils   utils;
    size_t i, itype;
    IOperand *ptr_ope;
    static std::string types[5] = { "int8", "int16", "int32", "float", "double" };
    std::vector<std::vector<t_token> >::iterator it = this->_ltokens.begin(), ite = this->_ltokens.end();
    for (;it != ite; ++it)
    {
        // std::vector<t_token>::iterator itt = it->begin();
        i = 0;
        while (AbstractVM::_instructions[i].name != it->at(0).value)
            i++;
        if ( AbstractVM::_instructions[i].value ) // takes a value as second token
        {
            type = 0;
            while (types[itype] != it->at(1).value)
                itype++;
            ptr_ope = utils.createOperand( static_cast<eOperandType>(itype), it->at(1).arg);
            AbstractVM::_instructions[i].f(ptr_ope);
        }
        else
            AbstractVM::_instructions[i].f(0);

    }
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
const char* AbstractVM::PopOnEmptyStack::what() const throw()
{
    return "Pop on empty stack";
}
const char* AbstractVM::ArithmeticNeedsTwoOperands::what() const throw()
{
    return "Pop on empty stack";
}


