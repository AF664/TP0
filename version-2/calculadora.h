#ifndef _CALCULADORA_H_INCLUDED_
#define _CALCULADORA_H_INCLUDED_

#include "bignum.h"
#include <iostream>
#include <string>


class calculadora
{
    private:
        bignum _operando1;
        bignum _operando2;
        status_t _estado;
        // puntero a función que devuelve bignum
        bignum (*_operacion)(const bignum &op1, const bignum &op2);

    public:
        
        calculadora(size_t precision);
        ~calculadora();

        void set_operacion(bignum (*f)(const bignum &op1, const bignum &op2));
        status_t estado();
        bool good();

        bignum resultado(const calculadora &);

        calculadora &operator=(const string &linea);

};

#endif
