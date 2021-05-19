#ifndef _CALCULADORA_H_INCLUDED_
#define _CALCULADORA_H_INCLUDED_

#include "bignum.h"
#include <iostream>
#include <string>
class calculadora
{
    private:
        bignum operando1;
        bignum operando2;
        // puntero a función que devuelve bignum
        bignum (*operacion)(const bignum &op1, const bignum &op2);
    public:
        calculadora();
        calculadora(std::string const &s);
        calculadora(const bignum &op1, const bignum &op2, bignum (*op)(const bignum &, const bignum &));
        bignum resultado(const calculadora &);


};

#endif
