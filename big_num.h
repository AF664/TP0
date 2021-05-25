#ifndef big_num_h
#define big_num_h

#include <string>
#include <iostream>

#define DEFAULT_PRECISION 20

using namespace std;

class BigNum{
    public:
        //Constructor por defecto
        BigNum();
        //Contructor por copia
        BigNum(const BigNum &);
        //Contructor por mediante vector de digitos
        BigNum(const unsigned short int*, const int l, int sign); 
        // Constructor "la construccion de la clase necesita un string y la precision"
        BigNum(string number, int p);
        //Destructor
        ~BigNum();    
        // Metodo mostrar
        void mostrar(); 
        // sobrecarga de operadores
        friend ostream& operator << (ostream& os, const BigNum &num);
        friend BigNum operator + (const BigNum &, const BigNum &);
        friend BigNum operator - (const BigNum &p1, const BigNum &p2);
        friend BigNum operator * (const BigNum &p1, const BigNum &p2);
        friend bool operator<(const BigNum &p1, const BigNum &p2);
        friend bool operator>(const BigNum &p1, const BigNum &p2);
        friend bool operator==(const BigNum &p1, const BigNum &p2);
        BigNum & operator=(const BigNum &orig);
        //Copia dos bignum
        void copiarBigNum(const BigNum &);
        // devuelve el signo del numero
        int get_sign();
        // devuelve valid_num
        bool get_valid_num();
        // cambio el valor del signo
        void set_sign(int s);
        private:
        // Defino variables caracteristicas de los numeros
        unsigned short int* digits;  // vector que contiene los numeros 
        int signo;                  // signo del numero que pasaron en la cadena
        int longitud;               // cantidad de digitos que tiene el vector digits
        int precision;              // cantidad de digitos con la cual se imprimer las operaciones
        bool valid_num;             // indica si el numero es valido, tiene una representacion en digits

};



#endif
