/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:41:02 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/17 16:12:20 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AbstractVM.hpp>
#include <string>

class IOperand
{
  public:
    virtual int getPrecision(void) const = 0;                         // Precision of the type of the instance
    virtual eOperandType getType(void) const = 0;                     // Type of the instance
    virtual IOperand const *operator+(IOperand const &rhs) const = 0; // Sum
    virtual IOperand const *operator-(IOperand const &rhs) const = 0; // Difference
    virtual IOperand const *operator*(IOperand const &rhs) const = 0; // Product
    virtual IOperand const *operator/(IOperand const &rhs) const = 0; // Quotient
    virtual IOperand const *operator%(IOperand const &rhs) const = 0; // Modulo
    virtual std::string const &toString(void) const = 0;              // String representation of the instance
    virtual ~IOperand(void) {}
};
