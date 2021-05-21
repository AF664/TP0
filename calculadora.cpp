#include <iostream>
#include <cstdlib>
#include <cstring>
#include "big_num.h"
#include "calculadora.h"

char * copiar_str(const string &, size_t, size_t);


//Constructor por defecto
calculadora::calculadora()
{
    operacion = 0;
}

//Constructor por copia
calculadora::calculadora(const calculadora &orig)
{
    operacion = orig.operacion;
    operando1.copiarBigNum(orig.operando1);
    operando1.copiarBigNum(orig.operando2);
}

//Contructor por string
calculadora::calculadora(string const &str, const int &p)
{
    size_t i, j = 0;
    string copia1, copia2;

    for(i = 0; str[i]!= ' ' && str[i]!= '\t' && str[i]!= '-' && str[i]!= '+' && str[i]!= '*' &&  str[i]; i++);
    copia1 = copiar_str(str, j, i);
    cout<<copia1<<endl;
    for(; str[i] == ' ' && str[i] == '\t'; i++);
    if(str[i] != '+' && str[i] != '-' && str[i] != '*')
    {
        operacion = 0;
        return;
    }
    cout<<str[i]<<endl;
    operacion = str[i];
    i++;
    for(; str[i] == ' ' && str[i] == '\t'; i++);
    j = i;
    while(str[i])
        i++;
    copia2 = copiar_str(str, j, i);
    cout<<copia2<<endl;

    BigNum aux1(copia1, p);
    BigNum aux2(copia2, p);
    operando1.copiarBigNum(aux1);
    operando2.copiarBigNum(aux2);
}

//Otro constructor
calculadora::calculadora(const BigNum &numero1, const BigNum &numero2, const char& op)
{
    operando1.copiarBigNum(numero1);
    operando2.copiarBigNum(numero2);
    operacion = op;
}

//Destructor
calculadora::~calculadora()
{

}

//Función que resuelve la operación dentro del objeto de tipo calculadora
BigNum calculadora::resolver()
{
    BigNum aux("-0", 1);

    cout<<"-"<<endl;
    if(operacion == '+')
    {
        cout<<"--"<<endl;
        return operando1 + operando2;
    }
    else if(operacion == '-')
        return operando1 - operando2;
    else if(operacion == '*')
        return operando1 * operando2;
    cout<<":("<<endl;
    return aux;
}

//
char * copiar_str(const string &orig, size_t inic, size_t fin)
{
    char *copia;
    size_t i, j;

    copia = new char[fin - inic];
    for(j = 0, i = inic; i < fin && orig[i]; i++, j++)
        copia[j] = orig[i];
    copia[j] = '\0';
    return copia;
}