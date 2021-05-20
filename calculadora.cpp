#include <iostream>
#include <cstdlib>
#include "big_num.h"
#include "calculadora.h"

//Constructor por defecto
calculadora::calculadora()
{

}

//Constructor por copia
calculadora::calculadora(const calculadora &cuenta)
{

}

//Constructor con string
calculadora::calculadora(const string & str)
{

}

//Otro constructor
calculadora::calculadora(const BigNum &operando1, const BigNum &operando2, BigNum (*op)(const BigNum &, const BigNum &))
{

}

//Destructor
calculadora::~calculadora()
{

}

//Función que resuelve la operación dentro del objeto de tipo calculadora
BigNum calculadora::resolver()
{
    BigNum p;
    return p;
}