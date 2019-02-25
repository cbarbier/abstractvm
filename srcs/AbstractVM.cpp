/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:51:53 by cbarbier          #+#    #+#             */
/*   Updated: 2019/01/22 17:28:32 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AbstractVM.hpp>
#include <Utils.hpp>
#include <iostream>
#include <fstream>

t_instr AbstractVM::_instructions[] = {
    {"push", 1, &AbstractVM::instr_push},
    {"pop", 0, &AbstractVM::instr_pop},
    {"dump", 0, &AbstractVM::instr_dump},
    {"assert", 1, &AbstractVM::instr_assert},
    {"add", 0, &AbstractVM::instr_add},
    {"sub", 0, &AbstractVM::instr_sub},
    {"mul", 0, &AbstractVM::instr_mul},
    {"div", 0, &AbstractVM::instr_div},
    {"mod", 0, &AbstractVM::instr_mod},
    {"print", 0, &AbstractVM::instr_print},
    {"and", 0, &AbstractVM::instr_and},
    {"or", 0, &AbstractVM::instr_or},
    {"xor", 0, &AbstractVM::instr_xor},
    {"exit", 0, &AbstractVM::instr_exit},
    {"", 0, 0}};

AbstractVM::AbstractVM(char *pfile) : _pfile(pfile)
{
    if (!pfile)
    {
        this->getInput(std::cin);
        return;
    }
    std::ifstream file;
    std::ios_base::iostate state = file.exceptions();
    file.exceptions(std::ifstream::badbit | std::ifstream::failbit); //catch (const std::ifstream::failure& e)

    try
    {
        file.open(pfile);
    }
    catch (const std::ifstream::failure &e)
    {
        std::cerr << "Error: opening / reading the file [" << pfile << "]" << std::endl;
        std::exit(1);
    }
    file.exceptions(state);
    this->getInput(file);
}

bool AbstractVM::isValidChars( std::string & line)
{
    bool ret = true;

    for ( size_t i = 0; i < line.length(); i++)
    {
        if ((line[i] < 32 || line[i] >= 127) && line[i] != '\n' && line[i] != '\t')
        {
            return false;
        }
    }
    return ret;
}

void AbstractVM::getInput(std::istream &is)
{
    int         i = 1;
    std::string line;

    while (!is.fail() && !is.eof())
    {
        std::getline(is, line, '\n');
        if (!this->isValidChars(line))
        {
            std::cerr << "Error: Invalid char @ line " << i << std::endl;
            std::exit(1);
        }
        if (line == ";;" && !this->_pfile)
            break;
        line = Utils::rmComment(line);
        this->_lines.push_back(line);
        i++;
    }
}

std::vector<std::string> &AbstractVM::getLines(void)
{
    return this->_lines;
}

AbstractVM::~AbstractVM()
{
    std::deque<const IOperand *>::iterator it = this->_deque.begin();
    std::deque<const IOperand *>::iterator ite = this->_deque.end();

    for (; it != ite; ++it)
        delete (*it);
    this->_lines.clear();
}

void AbstractVM::instr_push(const IOperand *ptr_ope, size_t row)
{
    static_cast<void>(row);
    this->_deque.push_back(ptr_ope);
}

void AbstractVM::instr_pop(const IOperand *ptr_ope, size_t row)
{
    static_cast<void>(ptr_ope);
    static_cast<void>(row);
    if (this->_deque.size() == 0)
        throw AbstractVM::PopEmptyStack();
    delete this->_deque.back();
    this->_deque.pop_back();
}

void AbstractVM::instr_dump(const IOperand *ptr_ope, size_t row)
{
    static_cast<void>(ptr_ope);
    static_cast<void>(row);
    std::deque<const IOperand *>::reverse_iterator it = this->_deque.rbegin();
    std::deque<const IOperand *>::reverse_iterator ite = this->_deque.rend();

    for (; it != ite; ++it)
        std::cout << (*it)->toString() << std::endl;
}

void AbstractVM::instr_assert(const IOperand *ptr_ope, size_t row)
{
    if (this->_deque.size() == 0)
        throw AbstractVM::PopEmptyStack();
    if (ptr_ope->getType() != this->_deque.back()->getType())
    {
        std::cerr << "Error: bas Assert on line" << row << std::endl;
        this->instr_exit(0, 0);
    }
}

void AbstractVM::instr_add(const IOperand *ptr_ope, size_t row)
{
    const IOperand *p1, *p2, *res;
    static_cast<void>(row);
    static_cast<void>(ptr_ope);
    if (this->_deque.size() < 2)
        throw AbstractVM::AbstractVM::ArithmeticNeedsTwoOperands();
    p2 = this->_deque.back();
    p1 = this->_deque.at(this->_deque.size() - 2);
    res = (*p1) + (*p2);
    this->_deque.pop_back();
    this->_deque.pop_back();
    this->_deque.push_back(res);
}

void AbstractVM::instr_sub(const IOperand *ptr_ope, size_t row)
{
    const IOperand *p1, *p2;
    static_cast<void>(row);
    static_cast<void>(ptr_ope);
    if (this->_deque.size() < 2)
        throw AbstractVM::AbstractVM::ArithmeticNeedsTwoOperands();
    p2 = this->_deque.back();
    this->_deque.pop_back();
    p1 = this->_deque.back();
    this->_deque.pop_back();
    this->_deque.push_back((*p1) - (*p2));
    delete p1;
    delete p2;
}

void AbstractVM::instr_mul(const IOperand *ptr_ope, size_t row)
{
    const IOperand *p1, *p2;
    static_cast<void>(row);
    static_cast<void>(ptr_ope);
    if (this->_deque.size() < 2)
        throw AbstractVM::AbstractVM::ArithmeticNeedsTwoOperands();
    p2 = this->_deque.back();
    this->_deque.pop_back();
    p1 = this->_deque.back();
    this->_deque.pop_back();
    this->_deque.push_back((*p1) * (*p2));
    delete p1;
    delete p2;
}

void AbstractVM::instr_div(const IOperand *ptr_ope, size_t row)
{
    const IOperand *p1, *p2;
    static_cast<void>(row);
    static_cast<void>(ptr_ope);
    if (this->_deque.size() < 2)
        throw AbstractVM::AbstractVM::ArithmeticNeedsTwoOperands();
    p2 = this->_deque.back();
    this->_deque.pop_back();
    p1 = this->_deque.back();
    this->_deque.pop_back();
    this->_deque.push_back((*p1) / (*p2));
    delete p1;
    delete p2;
}

void AbstractVM::instr_mod(const IOperand *ptr_ope, size_t row)
{
    const IOperand *p1, *p2;
    static_cast<void>(row);
    static_cast<void>(ptr_ope);
    if (this->_deque.size() < 2)
        throw AbstractVM::AbstractVM::ArithmeticNeedsTwoOperands();
    p2 = this->_deque.back();
    this->_deque.pop_back();
    p1 = this->_deque.back();
    this->_deque.pop_back();
    this->_deque.push_back((*p1) % (*p2));
    delete p1;
    delete p2;
}

void AbstractVM::instr_and(const IOperand *ptr_ope, size_t row)
{
    const IOperand *p1, *p2;
    static_cast<void>(row);
    static_cast<void>(ptr_ope);
    if (this->_deque.size() < 2)
        throw AbstractVM::AbstractVM::ArithmeticNeedsTwoOperands();
    p2 = this->_deque.back();
    this->_deque.pop_back();
    p1 = this->_deque.back();
    this->_deque.pop_back();
    this->_deque.push_back((*p1) & (*p2));
    delete p1;
    delete p2;
}
void AbstractVM::instr_or(const IOperand *ptr_ope, size_t row)
{
    const IOperand *p1, *p2;
    static_cast<void>(row);
    static_cast<void>(ptr_ope);
    if (this->_deque.size() < 2)
        throw AbstractVM::AbstractVM::ArithmeticNeedsTwoOperands();
    p2 = this->_deque.back();
    this->_deque.pop_back();
    p1 = this->_deque.back();
    this->_deque.pop_back();
    this->_deque.push_back((*p1) | (*p2));
    delete p1;
    delete p2;
}
void AbstractVM::instr_xor(const IOperand *ptr_ope, size_t row)
{
    const IOperand *p1, *p2;
    static_cast<void>(row);
    static_cast<void>(ptr_ope);
    if (this->_deque.size() < 2)
        throw AbstractVM::AbstractVM::ArithmeticNeedsTwoOperands();
    p2 = this->_deque.back();
    this->_deque.pop_back();
    p1 = this->_deque.back();
    this->_deque.pop_back();
    this->_deque.push_back((*p1) ^ (*p2));
    delete p1;
    delete p2;
}

void AbstractVM::instr_print(const IOperand *ptr_ope, size_t row)
{
    static_cast<void>(ptr_ope);

    if (!this->_deque.size())
    {
        throw AbstractVM::PrintEmptyStack();
    }
    const IOperand *top = this->_deque.back();
    if (top->getType() != Int8)
    {
        this->instr_exit(0, row);
    }

    char c = static_cast<char>(std::stoi(top->toString()));
    std::cout << c;
}

void AbstractVM::instr_exit(const IOperand *ptr_ope, size_t row)
{
    static_cast<void>(ptr_ope);
    static_cast<void>(row);
    std::exit(0);
}

void AbstractVM::exec(std::vector<std::vector<Analyzer::t_token> > tokens)
{
    Utils utils;
    size_t i, itype, row;
    const IOperand *ptr_ope;
    static std::string types[5] = {"int8", "int16", "int32", "float", "double"};
    // std::vector<std::vector<Analyzer::t_token> >::iterator it = this->_ltokens.begin(), ite = this->_ltokens.end();
    std::vector<std::vector<Analyzer::t_token> >::iterator it = tokens.begin(), ite = tokens.end();
    for (; it != ite; ++it)
    {
        try
        {
            this->debug();
            if (!it->size())
                continue;
            // std::vector<t_token>::iterator itt = it->begin();
            row = it->at(0).row;
            i = 0;
            while (AbstractVM::_instructions[i].name != it->at(0).value)
                i++;
            if (AbstractVM::_instructions[i].value) // takes a value as second token
            {
                itype = 0;
                while (types[itype] != it->at(1).value)
                    itype++;
                ptr_ope = utils.createOperand(static_cast<eOperandType>(itype), it->at(1).arg);
                // std::cout << AbstractVM::_instructions[i].name << " " << types[itype] << " " << ptr_ope->toString() << std::endl;
                (this->*AbstractVM::_instructions[i].f)(ptr_ope, row);
            }
            else
                (this->*AbstractVM::_instructions[i].f)(0, row);
        }
        catch (const std::exception &e)
        {
            std::cout << "\x1b[35mException: \x1b[0mParser line " << (row + 1) << " : "  << e.what() << std::endl;
        }
    }
}

void AbstractVM::debug(void)
{
    if (!DEBUG)
        return;
    std::deque<const IOperand *>::reverse_iterator it = this->_deque.rbegin();
    std::deque<const IOperand *>::reverse_iterator ite = this->_deque.rend();

    std::cout << "-------- n:" << this->_deque.size() << std::endl;
    if (!this->_deque.size())
        std::cout << "| empty" << std::endl;
    for (; it != ite; ++it)
        std::cout << "| " << (*it)->toString() << std::endl;
    std::cout << "--------" << std::endl;
}

const char *AbstractVM::MyException::what() const throw()
{
    return this->_mess.c_str();
}
const char *AbstractVM::Underflow::what() const throw()
{
    return this->_mess.c_str();
}
const char *AbstractVM::Overflow::what() const throw()
{
    return "Overflow";
}
const char *AbstractVM::DivByZero::what() const throw()
{
    return "Division by zero";
}
const char *AbstractVM::ModByZero::what() const throw()
{
    return "Modulo by zero";
}
const char *AbstractVM::PopEmptyStack::what() const throw()
{
    return "Pop Empty stack";
}
const char *AbstractVM::AssertEmptyStack::what() const throw()
{
    return "Assert Empty stack";
}
const char *AbstractVM::PrintEmptyStack::what() const throw()
{
    return "Print Empty stack";
}
const char *AbstractVM::ArithmeticNeedsTwoOperands::what() const throw()
{
    return "Arithemtic operation needs two operands";
}
