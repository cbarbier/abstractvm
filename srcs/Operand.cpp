/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:04:26 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/29 09:20:54 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Operand.hpp>
#include <Utils.hpp>
#include <AbstractVM.hpp>
#include <exception>
#include <iostream>
#include <sstream>
#include <cmath>

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

template<class T>
T Operand<T>::getValue( void ) const
{
    return this->_value;
}

template<class T>
eOperandType Operand<T>::getType( void ) const
{
    return static_cast<eOperandType>(0);
}

template<class T>
int Operand<T>::getPrecision( void ) const
{
    return this->getType();
}

template<class T> 
Operand<T>::Operand( T value )
{
    this->_value = value;
}

template<class T>
Operand<T>::Operand( const std::string & str )
{
    long double ld;
    if (!Utils::is_number(str, &ld))
        throw AbstractVM::MyException(std::string("Not a Valid Number"));
    if (std::numeric_limits<T>::max() < ld)
        throw AbstractVM::Overflow();
    if (std::numeric_limits<T>::min() > ld)
        throw AbstractVM::Underflow(std::string("Underflow"));
    this->_value = static_cast<T>(ld);
}

template<class T>
std::string const & Operand<T>::toString( void ) const {
	static std::string s = "";
    std::stringstream ss;
    ss << this->_value;
    s = ss.str();
    return s;
}

template<class T>
IOperand const *Operand<T>::operator+(IOperand const &rhs) const {
    Utils       utils;
    long double ld = std::stold(rhs.toString());

    eOperandType type = (this->getType() < rhs.getType() ? rhs.getType() : this->getType());
    return utils.createOperand(type, std::to_string((this->_value + ld)));
}

template<class T>
IOperand const *Operand<T>::operator-(IOperand const &rhs) const {
    Utils       utils;
    long double ld = std::stold(rhs.toString());

    eOperandType type = (this->getType() < rhs.getType() ? rhs.getType() : this->getType());
    return utils.createOperand(type, std::to_string((this->_value - ld)));
}

template<class T>
IOperand const *Operand<T>::operator/(IOperand const &rhs) const {
    Utils       utils;
    long double ld = std::stold(rhs.toString());

    if (!ld)
        throw AbstractVM::DivByZero();
    eOperandType type = (this->getType() < rhs.getType() ? rhs.getType() : this->getType());
    return utils.createOperand(type, std::to_string((this->_value / ld)));
}

template<class T>
IOperand const *Operand<T>::operator*(IOperand const &rhs) const {
    Utils       utils;
    long double ld = std::stold(rhs.toString());

    if (!ld)
        throw AbstractVM::DivByZero();
    eOperandType type = (this->getType() < rhs.getType() ? rhs.getType() : this->getType());
    return utils.createOperand(type, std::to_string((this->_value * ld)));
}

template<class T>
IOperand const *Operand<T>::operator%(IOperand const &rhs) const {
    Utils       utils;
    long double ld = std::stold(rhs.toString());

    if (!ld)
        throw AbstractVM::ModByZero();
    eOperandType type = (this->getType() < rhs.getType() ? rhs.getType() : this->getType());
    return utils.createOperand(type, std::to_string(fmod(static_cast<double>(this->_value), static_cast<double>(ld))));   
}

template<class T>
IOperand const *Operand<T>::operator&(IOperand const &rhs) const {
    Utils       utils;
    long int llr = std::stoll(rhs.toString());
    long int lll = static_cast<long int>(this->_value);

    if (this->getType() > Int32 || rhs.getType() > Int32)
        throw AbstractVM::MyException(std::string("Binary operator must be of intergral types"));
    eOperandType type = (this->getType() > rhs.getType() ? this->getType() : rhs.getType());
    return utils.createOperand(type, std::to_string((lll & llr)));
}

template<class T>
IOperand const *Operand<T>::operator|(IOperand const &rhs) const {
    Utils       utils;
    long int llr = std::stoll(rhs.toString());
    long int lll = static_cast<long int>(this->_value);

    if (this->getType() > Int32 || rhs.getType() > Int32)
        throw AbstractVM::MyException(std::string("Binary operator must be of intergral types"));
    eOperandType type = (this->getType() > rhs.getType() ? this->getType() : rhs.getType());
    return utils.createOperand(type, std::to_string((lll | llr)));
}

template<class T>
IOperand const *Operand<T>::operator^(IOperand const &rhs) const {
    Utils       utils;
    long int llr = std::stoll(rhs.toString());
    long int lll = static_cast<long int>(this->_value);

    if (this->getType() > Int32 || rhs.getType() > Int32)
        throw AbstractVM::MyException(std::string("Binary operator must be of intergral types"));
    eOperandType type = (this->getType() > rhs.getType() ? this->getType() : rhs.getType());
    return utils.createOperand(type, std::to_string((lll ^ llr)));
}


template<>
eOperandType	Operand<int8_t>::getType( void ) const			
{
    return Int8;
}

template<>
std::string const & Operand<int8_t>::toString( void ) const {
	static std::string s = "";
    std::stringstream ss;
    ss << static_cast<int>(this->_value);
    s = ss.str();
    return s;
}

template<>
eOperandType	Operand<int16_t>::getType( void ) const			
{
    return Int16;
}

template<>
eOperandType	Operand<int32_t>::getType( void ) const			
{
    return Int32;
}

template<>
eOperandType	Operand<float>::getType( void ) const			
{
    return Float;
}

template<>
eOperandType	Operand<double>::getType( void ) const			
{
    return Double;
}



template class Operand<double>;
template class Operand<float>;
template class Operand<int32_t>;
template class Operand<int16_t>;
template class Operand<int8_t>;
