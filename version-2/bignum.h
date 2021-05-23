#ifndef _BIGNUM_H_INCLUDED_
#define _BIGNUM_H_INCLUDED_

#include <iostream>
#include <string>
#include "errors.h"

typedef enum status{
    OK,
    ERROR_DIGITOS,
    ERROR_PRECISION,

} status_t;

class bignum
{
    private:
        unsigned short *_digitos;
        unsigned _largo;
        unsigned _precision;
        status_t _estado;

    public:
        bignum(unsigned precision);
        bignum(const bignum &original);
        ~bignum();

        short precision() const;
        short largo() const;
        status_t estado() const;
        bool good() const;

        bignum operator=(const bignum &original);
        bignum operator=(const string &linea);
        friend bignum operator+(const bignum &sumando1 , const bignum &sumando2);
        friend bignum operator-(const bignum &minuendo, const bignum &sustraendo);
        friend bignum operator*(const bignum &factor1, const bignum &factor2);
        friend std::ostream& operator<<(std::ostream& ,const bignum&);
        friend std::istream& operator>>(std::istream& , const bignum&);
};

#endif
