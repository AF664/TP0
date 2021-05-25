// archivo calculadora.cpp

#include "calculadora.h"

calculadora::calculadora(size_t precision = 0)
{   
    _operando1 = bignum(precision);
    _operando2 = bignum(precision);
    _estado = OK ;
    _operacion = NULL;
}

calculadora::~calculadora()
{}

void set_operacion(bignum (*f)(const bignum &op1, const bignum &op2))
{
    _operacion=f;

}