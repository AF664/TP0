
/*  
    Archivo: bignum.cpp
    Archivo de definición de las funciones de la clase bignum
*/

#include "bignum.h"

string DiccionarioOperaciones(OPERACIONES);
string DiccionarioDigitos("0123456789");

unsigned short *bignum::_crear_digitos(unsigned precision)
{
    unsigned short *digitos;
    
    digitos = precision ? new unsigned short[precision]: NULL;
    for( unsigned i=0; i< precision ; ++i)
        digitos[i]=0; 
    return digitos;
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
    _digitos = _crear_digitos(_precision);
    _signo = original._signo;

    for(size_t i=0; i<_largo;i++)
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
        _largo = original._largo;
        _estado = original._estado;
        _signo = original._signo;
    }
    return *this;
}

bignum &bignum::operator=(const string &linea)
{
    string aux(linea);
    size_t longitud = stringDigits(aux)-1;      

    if( !longitud )   
         _estado = ERROR_DIGITOS;
    else if(  longitud > _precision )
        _estado = ERROR_PRECISION;
    else {
        _estado = OK; 
        _signo = ( aux[0] == '+')? POSITIVO : NEGATIVO;
        _largo = longitud ;
        for(int i=longitud, j =0 ; i>0 ; --i , ++j)
            _digitos[j]= aux[i] -'0' ;                       
       
        for( unsigned i=longitud; i< _precision ; i++)
            _digitos[i]= 0;
        }
    return *this;

}

std::ostream& operator<<(std::ostream &fo,const bignum &numero)  
{
     
    fo<< (char) ((numero._signo == POSITIVO) ? ' ':'-' ) ;

    for(size_t i=numero._largo-1 ; i < numero._largo  ; --i)  
        fo << (char) (numero._digitos[i] + '0');
    return fo;
     
}
bignum operator+(const bignum &sumando1 , const bignum &sumando2)
{
    bignum suma( sumando1._precision);
    int signo1 = (sumando1._signo == POSITIVO ) ? 1 : -1 ; 
    int signo2 = (sumando2._signo == POSITIVO ) ? 1 : -1 ;
    int signo = sumando1._signo + sumando2._signo ; 
    int carry, parcial ;
    size_t i; // iterador; 


    if( !sumando1.good() || 
        !sumando2.good() || 
        sumando1._precision != sumando2._precision )
            suma._estado = NOK;
    else {

        // Para hacer la suma, en caso que haya un número negativo
        // se hace el complemento (de base 10)
        carry = signo;        
        for( i = 0 ; i < suma._precision ; ++i)
        {
            parcial =  signo*9 ;
            parcial += sumando1._digitos[i] * signo1;
            parcial += sumando2._digitos[i] * signo2; 
            parcial += carry;
            suma._digitos[i]= (parcial > 9)? parcial % 10 : parcial;
            carry = parcial / 10;
        }
        
        // Miro si hubo overflow
        signo -= carry ;
        if (signo < 0)
            suma._estado = ERROR_OVERFLOW;
        
        
        // en caso que quede negativo el resultado, hay que volver
        // a hacer el complemento (de base 10) del resultado
        else if ( signo == 1)
        {
            carry = 1;
            for( i = 0 ; i < suma._precision ; ++i)
            {
                parcial = carry + 9;
                parcial  -= suma._digitos[i];
                suma._digitos[i] = ( parcial > 9)? parcial % 10 : parcial;
                carry = parcial / 10;

            }
            
            suma._signo = NEGATIVO;
            suma._estado = OK;
        }
        else 
        {
            suma._signo = POSITIVO;
            suma._estado = OK;
        }
        
        for(i= suma._precision -1 ; suma._digitos[i] == 0 && i > 0; --i)
            ;
        suma._largo = i + 1;

        
    } // fin del else ( cuando no se detecta error de precision)
    return suma;
        
}

bignum operator-(const bignum &minuendo, const bignum &sustraendo)
{
    bignum resta(sustraendo);
    resta._signo = (resta._signo == POSITIVO) ? NEGATIVO : POSITIVO;
    return minuendo + resta;

}

#ifdef _TEST_BIGNUM
int main()
{
    bignum numero1(10);
    bignum numero2(10);
    bignum operacion;
    string linea;

    while( !cin.eof())
    {
        cout << "Prueba suma: ingrese primer valor"<< '\n';
        getline(cin,linea);
        numero1=linea;
        cout << "Prueba suma: ingrese segundo valor"<< '\n';
        getline(cin,linea);
        numero2=linea;
        operacion = numero1 + numero2;
        cout << numero1 << " + " << numero2 << " = " << operacion << '\n';
        cout << "estado: " << operacion.estado() << '\n';

        cout << "Prueba resta: ingrese primer valor"<< '\n';
        getline(cin,linea);
        numero1=linea;
        cout << "Prueba resta: ingrese segundo valor"<< '\n';
        getline(cin,linea);
        numero2=linea;
        operacion = numero1 - numero2;
        cout << numero1 << " - " << numero2 << " = " << operacion << '\n';
        cout << "estado: " << operacion.estado() << '\n';
    }
    
    return 0;
    
}
#endif
