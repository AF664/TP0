
/*  
    Archivo: bignum.cpp
    Archivo de definición de las funciones de la clase bignum
*/

#include "bignum.h"

string DiccionarioOperaciones(OPERACIONES);
string DiccionarioDigitos("0123456789");

unsigned short *_crear_digitos(unsigned precision)
{
    return precision ? new unsigned short[precision]: NULL;
}
bignum::bignum(unsigned precision=0)
{
    _digitos = _crear_digitos(precision);
    _precision = precision;
    _largo = 0;
    _signo = POSITIVO;
    _estado = OK;

}

bignum::bignum(const bignum &original)
{
    _precision = original._precision;
    _largo = original._largo;
    _digitos = new unsigned short[_precision];
    _signo = original._signo;

    for(int i=0; i<_largo;i++)
        _digitos[i]=original._digitos[i];
    _estado=OK;
}

bignum::bignum(const string &linea, size_t precision)
{
    
     _digitos = _crear_digitos(precision);
     _precision = precision;

     *this = linea;    

}

bignum::~bignum()
{
    if(_digitos!=NULL)
        delete [] _digitos;
    
}

size_t bignum::precision() const
{
    return _precision;
}

size_t bignum::largo() const
{
    return _largo;
}

signo_t bignum::signo() const
{
    return _signo;
}

status_t bignum::estado() const
{
    return _estado;
}

bool bignum::good() const
{
    return (_estado == OK)? true : false;
}

bignum &bignum::operator=(const bignum &original)
{
    if(this != &original)
    {
        if(_precision != original._precision)
        {
            delete [] _digitos;
            _precision = original._precision;
            _digitos= new unsigned short[_precision];
        }
        for(unsigned i=0; i< original._largo; i++)
            _digitos[i]=original._digitos[i];
        _largo=original._largo;
    }
    return *this;
}

bignum &bignum::operator=(const string &linea)
{
    string aux(linea);
    size_t longitud = stringDigits(aux);

    if( !longitud )   
         _estado = ERROR_DIGITOS;
    else if(  longitud > _precision )
        _estado = ERROR_PRECISION;
    else {
        _estado = OK; 
        _signo = ( aux[0] == '+')? POSITIVO : NEGATIVO;
        _largo = longitud -1 ;
        for(int i=longitud, j =0 ; i<0 ; --i , ++j)
            _digitos[j]= aux[i];
        
        }

}