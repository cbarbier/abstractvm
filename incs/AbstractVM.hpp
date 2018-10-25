/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:48:58 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/25 09:11:05 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP

#include <IOperand.hpp>
#include <deque>
#include <vector>
#include <string>


class AbstractVM;
typedef struct s_instr
{
    std::string name;
    char value;
    void (AbstractVM::*f)(IOperand *);
} t_instr;

class AbstractVM
{
  public:
    struct MyException : public std::exception
    {
        virtual const char *what() const throw();
    };
    struct Underflow : public std::exception
    {
        virtual const char *what() const throw();
    };
    struct Overflow : public std::exception
    {
        virtual const char *what() const throw();
    };
    struct DivByZero : public std::exception
    {
        virtual const char *what() const throw();
    };
    struct ModByZero : public std::exception
    {
        virtual const char *what() const throw();
    };
    struct PopOnEmptyStack : public std::exception
    {
        virtual const char *what() const throw();
    };
    struct ArithmeticNeedsTwoOperands : public std::exception
    {
        virtual const char *what() const throw();
    };



    AbstractVM(char *);
    AbstractVM(const AbstractVM &);
    AbstractVM &operator=(const AbstractVM &);
    ~AbstractVM();

    std::vector<std::string> &getLines(void);
    void getInput(std::istream &);

  private:
    AbstractVM();

    char *_pfile;
    std::vector<std::string> _lines;
    std::deque<IOperand *> _deque;
    std::vector<std::vector<t_token> > _ltokens;

    static t_instr _instructions[12];

    void exec(std::vector<std::vector<t_token> > &tokens);

    void instr_push( IOperand * );
    void instr_pop( IOperand * );
    void instr_dump( IOperand * );
    void instr_assert( IOperand * );
    void instr_add( IOperand * );
    void instr_sub( IOperand * );
    void instr_mul( IOperand * );
    void instr_div( IOperand * );
    void instr_mod( IOperand * );
    void instr_print( IOperand * );
    void instr_exit( IOperand * );
};

#endif // !ABSTRACTVM_HPP
