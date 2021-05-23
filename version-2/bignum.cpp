
/*  
    Archivo: bignum.cpp
    Archivo de definición de las funciones de la clase bignum
*/

#include "bignum.h"

bignum::bignum(unsigned precision=0)
{
    _digitos= precision ? new unsigned short(precision): NULL;
    _precision=precision;
    _largo=0;
    _estado= OK;

}

bignum::bignum(const bignum &original)
{
    _precision=original._precision;
    _largo=original._largo;
    _digitos=new unsigned short(_precision);

    for(int i=0; i<_largo;i++)
        _digitos[i]=original._digitos[i];
    _estado=OK;
}

