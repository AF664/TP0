#ifndef _BIGNUM_H_INCLUDED_
#define _BIGNUM_H_INCLUDED_

#include <iostream>
#include <string>

class bignum
{
    private:
        unsigned short *digits;
        unsigned short lengh;
        unsigned short precision;

    public:
        bignum();
        bignum(std::string const &number,short precision);
        ~bignum();
        short precision(const bignum &);
        short lengh(const bignum &);

        friend bignum operator+(const bignum&, const bignum&);
        friend bignum operator-(const bignum&, const bignum&);
        friend bignum operator*(const bignum&, const bignum&);
        friend std::ostream& operator<<(std::ostream& ,const bignum&);
        friend std::istream& operator>>(std::istream& , const bignum&);

#endif
