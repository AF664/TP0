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
    size_t i, k, j = 0;
    string copia1, copia2;
    bool neg_num1 = false;
    // recorro el str hasta que encuentro la posicion del primer numero
    for(k = 0; !isdigit(str[k]) && str[k];k++) if(str[k] == '-') neg_num1 = true;
    // Busco el primer numero
    for(i = k; str[i]!= ' ' && str[i]!= '\t' && str[i]!= '-' && str[i]!= '+' && str[i]!= '*' &&  str[i]; i++);
    copia1 = copiar_str(str, k, i);
    if(neg_num1) copia1 = '-' + copia1;
    cout<<copia1<<endl;
    // recorro el str hasta que encuentro la posicion de la operacion
    for(; str[i] == ' ' || str[i] == '\t'; i++);
    if(str[i] != '+' && str[i] != '-' && str[i] != '*')
    {
        operacion = 0;
        return;
    }
    cout<<str[i]<<endl;
    operacion = str[i++];
    // recorro el str hasta que encuentro la posicion del segundo numero
    for(; str[i] == ' ' || str[i] == '\t'; i++);
    j = i;
    while(str[i++]);
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
    int signo1 = operando1.get_sign();
    int signo2 = operando2.get_sign();

    cout<<"--  Selecciono la operacion  --"<<endl;
    // para el caso que la operacion este mal formulada devulvo un BigNum vacio
    // por defecto
    bool a = operando1.get_valid_num() & operando2.get_valid_num();
    if(!a)return BigNum();
    if(operacion == '+')
    {
        // para el caso de suma de 2 numeros con mismo signo
        if(signo1 + signo2 == 0)return operando1 + operando2;
        else{
            // num1 positivo pero num2 negativo = num1 - num2 (cambio de signo a num2)
            if(signo1 < signo2){
                operando2.set_sign(0);
                return operando1 - operando2;
            }
            // num2 positivo pero num1 negativo = num2 - num1
            else{
                operando1.set_sign(0);
                return operando2 - operando1;
            } 
        }
        
    }
    else if(operacion == '-'){
        // si num2 + y num1 + 
        if(signo1 + signo2 == 0)return operando1 - operando2;
        // si num2 - y num1 -
        if(signo1 + signo2 == 2){
            // le cambio el signo operando 2 (pasa a ser positivo) y 
            // le cambio el signo a operando 1 () 
            // los resto 
            operando2.set_sign(0);
            operando1.set_sign(0);
            return operando2 - operando1;
        }
        // op1 + y op2 - , es una suma
        if(signo1<signo2){
            // aca la suma es entre dos numeros positivos
            operando2.set_sign(0);
            return operando2 + operando1;
        }
        // lo podemos ver como la suma de 2 numeros negativos
        if(signo1>signo2){
            // cambio el signo del del op2 a - 
            operando2.set_sign(1);
            return operando2 + operando1;
        } 
    }
        
    else if(operacion == '*')
        // aca no importa el signo
        return operando1 * operando2;
    // Cuando el operando no es valido 
    cout<<":("<<endl;
    // devuelvo un BigNum vacio por defecto
    return BigNum();
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