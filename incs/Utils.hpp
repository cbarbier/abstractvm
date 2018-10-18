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

#include <iostream>

class Utils
{
  public:
    virtual ~Utils(){}

    static std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
    static std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
    static std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
    static std::string& rmComment(std::string& str, const std::string& chars = ";");
   
};

#endif
