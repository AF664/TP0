// archivo calculadora.cpp

#include "calculadora.h"

using namespace std ;

char DiccionarioOperaciones[]= {'+','-','*','\0'};

calculadora::calculadora(unsigned precision =0 )
{   
    
    _operando1 = bignum(precision);
    _operando2 = bignum(precision);
    _estado = OK ;
    _operacion = NO_OP;
}

calculadora::calculadora()
{
    _operando1 = bignum(0);
    _operando2 = bignum(0);
     _estado = OK ;
    _operacion = NO_OP;
}

calculadora::~calculadora()
{}

void calculadora::_actualizar_estado()
{
    _estado = (_operando1.good() == OK && _operando2.good() == OK) ? OK : NOK ;
}

void calculadora::set_operacion(operacion_t op)
{
    _operacion=op;
}

status_t calculadora::estado()
{
    this->_actualizar_estado();
    return _estado;
}

bool calculadora::good()
{
    this->_actualizar_estado();
    return (_estado == OK ? true : false );
}

bignum calculadora::resultado() const
{
        
    if( _operacion == SUMAR)
        return _operando1 + _operando2;
    
    if( _operacion == RESTAR)
        return _operando1 - _operando2;
    
    if( _operacion == MULTIPLICAR)
        return _operando1 * _operando2;

    return bignum(0);
}

calculadora &calculadora::operator=(const string &linea)
{
    unsigned i; // iterador
    size_t num1 = linea.find_first_of("0123456789");
    size_t op = linea.find_first_of(DiccionarioOperaciones, num1);

    string sbignum1 = linea.substr(0,op);
    string sop = linea.substr(op,1);
    string sbignum2 = linea.substr(op+1);

    _operando1 = sbignum1;
    _operando2 = sbignum2;


     for( i=0 ; i< NO_OP && sop.find(DiccionarioOperaciones[i]) == std::string::npos ; i++)
        ;

    _operacion = ( i < NO_OP) ? ( operacion_t )i : NO_OP;

    this->_actualizar_estado();
    return *this;

}

#ifdef _TEST_CALCULADORA
 
 int main()
 {
     calculadora operacion(20);
     string linea;

     while(!cin.eof())
     {
         cout << "Ingrese la cuenta: " << '\n';
         getline(cin,linea);
         operacion = linea;
         cout << operacion.resultado() << '\n';

     }

 }

 #endif