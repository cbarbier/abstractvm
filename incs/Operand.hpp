/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 10:05:27 by cbarbier          #+#    #+#             */
/*   Updated: 2019/02/25 10:30:55 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include <iostream>

template <typename T>
class Operand : public IOperand
{
  public:
    Operand(void);
    Operand( T val );
    Operand(const Operand &rhs);
    Operand( const std::string & );
    Operand &operator=(const Operand &rhs);
    ~Operand(void);
    eOperandType getType(void) const;
    int getPrecision(void) const;
    IOperand const *operator+(IOperand const &rhs) const;
    IOperand const *operator-(IOperand const &rhs) const;
    IOperand const *operator*(IOperand const &rhs) const;
    IOperand const *operator/(IOperand const &rhs) const;
    IOperand const *operator%(IOperand const &rhs) const;
    IOperand const *operator&(IOperand const &rhs) const;
    IOperand const *operator|(IOperand const &rhs) const;
    IOperand const *operator^(IOperand const &rhs) const;

    std::string const &toString(void) const;              // String representation of the instance;
    T getValue( void ) const;

  private:
    T      _value;
};

#endif // !OPERAND_HPP
