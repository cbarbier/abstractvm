/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 13:41:26 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/18 16:50:28 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Utils.hpp>

std::string& Utils::ltrim(std::string& str, const std::string& chars)
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}
 
std::string& Utils::rtrim(std::string& str, const std::string& chars)
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}
 
std::string& Utils::trim(std::string& str, const std::string& chars)
{
    return ltrim(rtrim(str, chars), chars);
}

std::string& Utils::rmComment(std::string& str, const std::string& chars)
{
    str = str.substr(0, str.find_first_of(chars));
    return ltrim(rtrim(str, chars), chars);
}

bool Utils::is_number(const std::string& s, double *ptr_d)
{
    try
    {
        *ptr_d = std::stod(s);
    }
    catch(...)
    {
        std::cerr << "Error: can't convert to double" << std::endl;
        return false;
    }
    return true;
}

IOperand const * Utils::createInt8( std::string const & value ) const
{
    (void)value;
    return 0;
}

IOperand const * Utils::createInt16( std::string const & value ) const
{
    (void)value;
    return 0;
}

IOperand const * Utils::createInt32( std::string const & value ) const
{
    (void)value;
    return 0;
}

IOperand const * Utils::createFloat( std::string const & value ) const
{
    (void)value;
    return 0;
}

IOperand const * Utils::createDouble( std::string const & value ) const
{
    (void)value;
    return 0;
}

IOperand const * Utils::createOperand( eOperandType type, std::string const & value ) const
{
    (void)type;
    (void)value;
    static IOperand const *(Utils::*arr_f[5])( std::string const &) const = 
                {&Utils::createInt8,
                 &Utils::createInt16,
                 &Utils::createInt32,
                 &Utils::createFloat,
                 &Utils::createDouble};
    return (this->*arr_f[type])(value);
}
