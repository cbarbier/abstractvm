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
    void (AbstractVM::*f)(void);
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

    static t_instr _instructions[12];

    void instr_push(void);
    void instr_pop(void);
    void instr_dump(void);
    void instr_assert(void);
    void instr_add(void);
    void instr_sub(void);
    void instr_mul(void);
    void instr_div(void);
    void instr_mod(void);
    void instr_print(void);
    void instr_exit(void);
};

#endif // !ABSTRACTVM_HPP
