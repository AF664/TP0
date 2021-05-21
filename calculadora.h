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
        char operacion;
    public:
        calculadora();
        calculadora(const calculadora &);
        calculadora(const string &, const int &);
        calculadora(const BigNum &, const BigNum &, const char &);
        ~calculadora();
        BigNum resolver();
        void setOperacion(const char &);
};

#endif
