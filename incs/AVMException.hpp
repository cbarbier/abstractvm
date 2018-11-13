/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVMException.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 10:05:27 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/26 10:33:30 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVMEXCEPTION_HPP
#define AVMEXCEPTION_HPP

#include <exception>
#include <string>

class AVMException : public std::runtime_error
{
  public:
    AVMException(const AVMException &rhs);
    AVMException( std::string mess );
    AVMException &operator=(const AVMException &rhs);
    ~AVMException(void) throw();

    const char *what() const throw();
  private:
    AVMException(void);
  protected:
    std::string    _mess;
};

#endif // !AVMException_HPP
