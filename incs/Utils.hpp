/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 10:05:27 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/18 11:52:38 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <IOperand.hpp>
#include <iostream>

class Utils
{
  public:
    virtual ~Utils( void ){}

    static std::string& ltrim(std::string& str, const std::string& chars = "\n");
    static std::string& rtrim(std::string& str, const std::string& chars = "\n");
    static std::string& trim(std::string& str, const std::string& chars = "\n");
    static std::string& rmComment(std::string& str, const std::string& chars = ";");
    static bool is_number( const std::string &, long double *);
   
    IOperand const * createOperand( eOperandType type, std::string const & value ) const;
   private:
    IOperand const * createInt8( std::string const & value ) const;
    IOperand const * createInt16( std::string const & value ) const;
    IOperand const * createInt32( std::string const & value ) const;
    IOperand const * createFloat( std::string const & value ) const;
    IOperand const * createDouble( std::string const & value ) const;
};

#endif
