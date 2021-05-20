#ifndef _CALCULADORA_H_INCLUDED_
#define _CALCULADORA_H_INCLUDED_

#include "big_num.h"
#include <iostream>
#include <string>


using namespace std;

class calculadora
{
    private:
        BigNum operando1;
        BigNum operando2;
        // puntero a función que devuelve BigNum
        BigNum (*operacion)(const BigNum &op1, const BigNum &op2);
    public:
        calculadora();
        calculadora(const calculadora &);
        calculadora(string const &);
        calculadora(const BigNum &, const BigNum &, BigNum (*op)(const BigNum &, const BigNum &));
        ~calculadora();
        BigNum resolver();

};

#endif
