/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:04:26 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/23 09:23:31 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Operand.hpp>
#include <Utils.hpp>
#include <AbstractVM.hpp>
#include <exception>
#include <iostream>

template <class T>
Operand<T>::Operand( void )
{
    this->_value = static_cast<T>(0);
}

template <class T>
Operand<T>::~Operand( void )
{
}

template<class T>
Operand<T>::Operand( Operand<T> const & obj )
{
    *this = obj;
}

template<class T>
Operand<T> & Operand<T>::operator=( Operand<T> const & rhs )
{
    this->_value = rhs._value;
    return *this;
}

template<class T> Operand<T>::Operand( T value )
{
    this->_value = value;
}

template<class T> Operand<T>::Operand( std::string & str )
{
    long double ld;
    T      val;
    if (!Utils::is_number(str, &ld))
        throw AbstractVM::MyException();
    if (std::numeric_limits<T>::max < ld)
        throw AbstractVM::Overflow();
    if (std::numeric_limits<T>::min > ld)
        throw AbstractVM::Underflow();
    this->_value = std::to_string(static_cast<T>(ld));
}

template<class T>
std::string const & Operand<T>::toString( void ) const {
	return std::to_string(this->_value);
}

template<class T>
IOperand const *Operand<T>::operator+(IOperand const &rhs) const {
    Utils       utils;
    long double ld = std::stold(rhs.toString());

    eOperandType type = (this->getPrecision() < rhs.getPrecision() ? rhs.getType() : this->getType());
    return utils.createOperand(type, std::to_string(this->_value + ld));
}

template<class T>
IOperand const *Operand<T>::operator/(IOperand const &rhs) const {
    Utils       utils;
    long double ld = std::stold(rhs.toString());

    if (!ld)
        throw AbstractVM::DivByZero();
    eOperandType type = (this->getPrecision() < rhs.getPrecision() ? rhs.getType() : this->getType());
    return utils.createOperand(type, std::to_string(this->_value / ld));
}
