#ifndef _BIGNUM_H_INCLUDED_
#define _BIGNUM_H_INCLUDED_

#include <iostream>
#include <string>
#include <cctype>
#include "utils.h"
using namespace std;

typedef enum status{
    OK,
    NOK,
    ERROR_DIGITOS,
    ERROR_PRECISION,
    ERROR_OVERFLOW

} status_t;

 typedef enum signo{
     POSITIVO=0,
     NEGATIVO=1
 } signo_t;


#define OPERACIONES "+-*"

enum operaciones {
    SUMA,
    RESTA,
    MULTIPLICACION
};


class bignum
{
    private:
        unsigned short *_digitos;
        size_t _largo;
        size_t _precision;
        signo_t _signo;
        status_t _estado;

        // Asigna memoria a los digitos
        unsigned short *_crear_digitos(unsigned precision);

        
    public:
        bignum(unsigned precision);
        bignum(const bignum &original);
        bignum(const string &linea, size_t precision);
        ~bignum();

        size_t precision() const;
        size_t largo() const;
        signo_t signo() const;
        status_t estado() const;
        bool good() const;

        bignum &operator=(const bignum &original);
        bignum &operator=(const string &linea) ;
        friend bignum operator+(const bignum &sumando1 , const bignum &sumando2);
        //friend bignum operator-(const bignum &minuendo, const bignum &sustraendo);
        //friend bignum operator*(const bignum &factor1, const bignum &factor2);
        friend std::ostream& operator<<(std::ostream& ,const bignum&);
        //friend std::istream& operator>>(std::istream& , const bignum&);
};

#endif
