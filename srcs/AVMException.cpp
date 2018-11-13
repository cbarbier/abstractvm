/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVMException.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 13:41:26 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/19 13:48:12 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AVMException.hpp>

AVMException::AVMException(std::string mess): std::runtime_error(mess), _mess(mess)
{
}
 
AVMException::AVMException(const AVMException &rhs):std::runtime_error(rhs._mess), _mess(rhs._mess)
{
}

AVMException &AVMException::operator=(const AVMException &rhs)
{
    this->_mess = rhs._mess;
    return (*this);
}

AVMException::~AVMException() throw()
{

}

const char      *AVMException::what() const throw()
{
    return this->_mess.c_str();
}
