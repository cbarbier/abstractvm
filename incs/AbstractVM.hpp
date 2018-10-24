/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:48:58 by cbarbier          #+#    #+#             */
/*   Updated: 2018/10/24 09:05:16 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP

#include <vector>
#include <string>



class AbstractVM
{
public:

    struct MyException: public std::exception{
         virtual const char* what() const throw ();
    };
    struct Underflow: public std::exception{
         virtual const char* what() const throw ();
    };
    struct Overflow: public std::exception{
         virtual const char* what() const throw ();
    };
    struct DivByZero: public std::exception{
         virtual const char* what() const throw ();
    };
    struct ModByZero: public std::exception{
         virtual const char* what() const throw ();
    };

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
    
    typedef struct s_instr {
        std::string name;
        char        value;
        void        (*f)( void );
    }

    t_instr     _instructions[];
        
};

#endif // !ABSTRACTVM_HPP
