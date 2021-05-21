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
        // Constructor "la construccion de la clase necesita un string y la precision"
        BigNum(string number, int p);
        // Metodo Suma
        BigNum* suma(BigNum* number);
        //friend BigNum operator+(BigNum b1, const BigNum &b2); // para usar "+" entre bigNum
        // Metodo resta
        BigNum* resta(BigNum* number);
        // Metodo multiplicacion
        BigNum* multiplicacion(BigNum* number);
        // Metodo mostrar
        void mostrar(); 
        // sobrecarga de operadores
        friend ostream& operator << (ostream& os, const BigNum &num);
        friend BigNum operator + (const BigNum &p1, const BigNum &p2);
        friend BigNum operator - (const BigNum &p1, const BigNum &p2);
        friend BigNum operator * (const BigNum &p1, const BigNum &p2);
        ~BigNum();     
    private:
        // Defino variables caracteristicas de los numeros
        unsigned short int* digits;  // vector que contiene los numeros 
        int signo;                  // signo del numero que pasaron en la cadena
        int longitud;               // cantidad de digitos que tiene el vector digits
        int precision;              // cantidad de digitos con la cual se imprimer las operaciones


};



#endif