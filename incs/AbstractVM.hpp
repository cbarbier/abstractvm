/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:48:58 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/18 17:00:08 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP

#include <vector>
#include <string>

enum eOperandType {
    Int8,
    Int16,
    Int32,
    Float,
    Double
};

class AbstractVM
{
public:
    AbstractVM( char * );
    AbstractVM(const AbstractVM &);
    AbstractVM &operator=(const AbstractVM &);
    ~AbstractVM();

    std::vector<std::string> & getLines( void );
    void getInput( std::istream & );

private:
    AbstractVM();

    char    * _pfile;
    std::vector<std::string> _lines;
};

#endif // !ABSTRACTVM_HPP
