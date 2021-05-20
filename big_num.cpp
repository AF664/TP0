#include <string>
#include <iostream>
#include "big_num.h"
using namespace std;


//Constructor por defecto
BigNum::BigNum()
{

}

//Constructor por copia
BigNum::BigNum(const BigNum &num)
{

}

/* Constructor de la clase BigNum
    Este metodo tiene como entrada un string 'number' que contiene el numero Ej:-76543
    y devuelve una clase BigNum que contiene la informacion de 'number' en sus atributos.
    Ej:
        signo = 1
        digits = 345670
        precision = p

        guardo los digitos al revez. ()
*/
BigNum::BigNum(string numero, int p){
    int indice = 0, largo_s = numero.size();
    precision = p;
    longitud = largo_s;
    signo = 0;
    // creo un vector con todos los valores en cero
    digits = new unsigned short int [largo_s];
    // Numero negativo tiene - al inicio del str.
    if(numero[0] == '-'){
        signo = 1;
        indice++;
        longitud--;
        largo_s--;
    }
    for(int i = largo_s - 1;i >= 0; i--){
        digits[largo_s -1 - i] = numero[i + signo] - '0';
    }
    
}


BigNum* BigNum::suma(BigNum* number){
    int carry = 0;
    int largo = max(longitud, number->longitud);
    int corto = min(longitud, number->longitud);
    unsigned short int* resultado = new unsigned short int[largo + 1]; 
    BigNum* resultado_b = new BigNum("0",90);
    resultado_b->digits = resultado; 
    resultado_b->longitud = largo;
    BigNum *n_largo, *n_corto;
    if(corto == longitud){
        n_largo = (BigNum*)number;
        n_corto = this; 
    }else{
        n_largo = this;
        n_corto = (BigNum*)number;        
    }   
    for(int i = 0; i< corto; i++){
        int parcial = 0;
        parcial = carry + n_largo->digits[i] + n_corto->digits[i];
        if(parcial >= 10){
            parcial-=10;
            carry = 1;
        }else{
            carry = 0;
        }
        cout << "Sumo: "<< n_largo->digits[i] << " + carry + " << n_corto->digits[i] << " = " << parcial << " + carry= "<< carry*10 << endl;
        resultado[i] = parcial;
    }
    for(int k = corto;k < largo; k++){
        int parcial = 0;
        parcial = carry + n_largo->digits[k];
        if(parcial >= 10){
            parcial-=10;
            carry = 1;
        }else{
            carry = 0;
        }        
        cout << "Sumo: "<< n_largo->digits[k] << " + 0 = "  << parcial << " + carry= "<< carry*10 << endl;
        resultado[k] = parcial;
        
    }
    if(carry){
        resultado[largo] = carry;
        resultado_b->longitud++;
    }
    
    cout << "Sumo: " << resultado[largo] << endl;
    n_largo = NULL;
    n_corto = NULL; 
    return resultado_b;
}

BigNum* BigNum::resta(BigNum* number){
    return number;
}

BigNum* BigNum::multiplicacion(BigNum* number){
    int carry = 0;
    int arriba = max(longitud, number->longitud);
    int abajo = min(longitud, number->longitud);  
    unsigned short int* resultado = new unsigned short int[arriba + abajo + 1];
    BigNum* n_resultado = new BigNum("0",90);
    n_resultado->digits = resultado; 
    n_resultado->longitud = arriba + abajo + 1;
    BigNum *n_arriba, *n_abajo; 
    if(abajo == longitud){
        n_arriba = (BigNum*)number;
        n_abajo = this; 
    }else{
        n_arriba = this;
        n_abajo = (BigNum*)number;        
    } 
    // aca comienza la multiplicacion
    for(int i = 0; i < abajo; i++){
        for(int k = 0; k < arriba; k++){
            int parcial = n_abajo->digits[i] * n_arriba->digits[k];
            if(parcial >= 10){
                carry = parcial / 10;
                parcial = parcial - (carry * 10);
            }else{
                carry = 0;
            }       
            resultado[k] += parcial;
            resultado[k+1] = carry;
            cout << resultado[k];
            //cout << n_abajo->digits[i] << " * " << n_arriba->digits[k] << " = " << n_abajo->digits[i] * n_arriba->digits[k] << endl;
        }
    }


    // asigno signo a resultado
    if(n_arriba->signo == n_abajo->signo) n_resultado->signo = 0;
    else n_resultado->signo = 1;
    
    return n_resultado;
}

void BigNum::mostrar(){
    cout << "El número almacenado tiene signo " << signo << " y es el: ";
    for (int i = 0; i < longitud; i++) {
        cout << digits[longitud - 1 - i];
    }
    cout << endl;
}

BigNum::~BigNum(){
    cout<<"Ejecutando destructor de clase BigNum para el objeto: "<< this <<endl;
    delete digits;
} 

// --------------------------------------------------------------
//                      Sobrecarga de operadores
//
// Sobrecarga del operador +
BigNum operator + (const BigNum &p1, const BigNum &p2)
{
    return p1;
}


// Sobrecarga del operador -
BigNum operator - (const BigNum &p1, const BigNum &p2){
    return p1;
}

// Sobrecarga del operador *
BigNum operator * (const BigNum &p1, const BigNum &p2){
    return p1;
}

ostream& operator << (ostream& os, const BigNum &dt)
{
    os << "El número almacenado tiene signo " << dt.signo << " y es el: ";
    int imprimir = min(dt.precision, dt.longitud);
    for (int i = 0; i < imprimir; i++) {
        os << dt.digits[imprimir - 1 - i];
    }
    os << endl;
    return os;
}