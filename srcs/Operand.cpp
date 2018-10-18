/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:04:26 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/18 17:06:37 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Operand.hpp>
#include <iostream>

template <class T>
Operand::Operand( void )
{
    this->_value = std::to_string(static_cast<T>(0));
}

template <class T>
Operand::~Operand( void )
{
}

template<class T>
Operand<T>::Operand( Operand<T> const & obj )
{
    *this = obj;
}

template<class T> Operand<T> & Operand<T>::operator=( Operand<T> const & rhs )
{
    this->_value = rhs._value;
    return *this;
}

template<class T> Operand<T>::Operand( T value )
{
    this->_value = std::to_string(value);
}

template<class T> Operand<T>::Operand( std::string str )
{
    double d;
    if (Utils::is_number(str, &d))
        this->_value = std::to_string(static_cast<T>(d));
}

template<class T>
std::string const & Operand<T>::toString( void ) const {
	return this->_value;
}
