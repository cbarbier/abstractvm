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
