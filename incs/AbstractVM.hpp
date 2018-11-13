/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:48:58 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/26 10:33:16 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP

#define DEBUG 0

#include <AVMException.hpp>
#include <IOperand.hpp>
#include <Analyzer.hpp>
#include <deque>
#include <vector>
#include <string>


class AbstractVM;
typedef struct s_instr
{
    std::string name;
    char value;
    void (AbstractVM::*f)(const IOperand *, size_t row);
} t_instr;

class AbstractVM
{
  public:
    struct MyException : public AVMException
    {
        MyException( std::string mess ): AVMException(mess){};
        virtual const char *what() const throw();
    };
    struct Underflow : public AVMException
    {
        Underflow( std::string mess ): AVMException(mess){};
        const char *what() const throw();
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
    struct PopEmptyStack : public std::exception
    {
        virtual const char *what() const throw();
    };
    struct AssertEmptyStack : public std::exception
    {
        virtual const char *what() const throw();
    };
    struct PrintEmptyStack : public std::exception
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
    void exec(std::vector<std::vector<Analyzer::t_token> > tokens);

    void debug();

  private:
    AbstractVM();

    char *_pfile;
    std::vector<std::string> _lines;
    std::deque<const IOperand *> _deque;
    // std::vector<std::vector<Analyzer::t_token> > _ltokens;

    static t_instr _instructions[15];


    void instr_push( const IOperand *, size_t );
    void instr_pop( const IOperand *, size_t );
    void instr_dump( const IOperand *, size_t );
    void instr_assert( const IOperand *, size_t );
    void instr_add( const IOperand *, size_t );
    void instr_sub( const IOperand *, size_t );
    void instr_mul( const IOperand *, size_t );
    void instr_div( const IOperand *, size_t );
    void instr_mod( const IOperand *, size_t );
    void instr_print( const IOperand *, size_t );
    void instr_exit( const IOperand *, size_t );
    void instr_and( const IOperand *, size_t );
    void instr_or( const IOperand *, size_t );
    void instr_xor( const IOperand *, size_t );
};

#endif // !ABSTRACTVM_HPP
