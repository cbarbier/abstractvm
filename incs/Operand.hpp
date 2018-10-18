/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 10:05:27 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/18 15:04:28 by cbarbier         ###   ########.fr       */
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
    Operand<T>(void)
    Operand<T>( T val )
    Operand<T>(const Operand<T> &rhs)
    Operand<T> &operator=(const Operand<T> &rhs)
    ~Operand<T>(void)
    eOperandType getType(void) const
    int getPrecision(void) const
    IOperand const *operator+(IOperand const &rhs) const
    IOperand const *operator-(IOperand const &rhs) const
    IOperand const *operator*(IOperand const &rhs) const
    IOperand const *operator/(IOperand const &rhs) const
    IOperand const *operator%(IOperand const &rhs) const
    std::string const &toString(void) const;              // String representation of the instance

  private:
    std::string _value;
};

#endif // !OPERAND_HPP
