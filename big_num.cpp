#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include "big_num.h"

using namespace std;


//Constructor por defecto
BigNum::BigNum()
{
    precision = DEFAULT_PRECISION;
    digits = NULL;
    signo = 0;
    valid_num = false;              // indica que no es un numero util
}

//Constructor por copia
BigNum::BigNum(const BigNum &orig)
{
    this->digits = NULL;
    (*this).copiarBigNum(orig);
}

// constructor con vector de digitos. 
BigNum::BigNum(const unsigned short int* vector, const int largo, int sign){
    precision = DEFAULT_PRECISION;      
    longitud = largo;
    valid_num = true;
    signo = sign;
    digits = new unsigned short int [largo];

    for(int i = 0;i < largo; i++){
        digits[i] = vector[i];
    }
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
BigNum::BigNum(string numero, int p)
{
    int indice = 0, largo_s = numero.length();
    precision = p;
    longitud = largo_s;
    signo = 0;
    valid_num = true;

    // Numero negativo tiene - al inicio del str.
    if(numero[0] == '-' || numero[0] == '+'){
        signo = numero[0] == '-' ? 1 : 0;
        indice++;
        longitud--;
        largo_s--;
    }
    // creo un vector con todos los valores en cero
    digits = new unsigned short int [largo_s];
    int k;
    for(int i = largo_s - 1; i >= indice; i--){
        string cad1;
        cad1 = numero[i + indice] + '\0';     // tomo solo un digito del numero

        try
        {
            digits[largo_s - 1 - i] = stoi(cad1, NULL, 10);
            k = digits[largo_s - 1 - i];
        }
        catch(const std::exception& e)
        {
            std::cerr <<"Conversion error "<< e.what() << '\n';
            valid_num = false;
            break;
        }
    }
    
}


void BigNum::suma(const BigNum* number, BigNum* resul){
    int carry = 0;
    int largo = max(longitud, number->longitud);
    int corto = min(longitud, number->longitud);
    unsigned short int* resultado = new unsigned short int[largo + 1]; 
    BigNum *n_largo, *n_corto;

    // distingo por el largo de los numeros
    if(corto == longitud){
        n_largo = (BigNum*)number;
        n_corto = this; 
    }else{
        n_largo = this;
        n_corto = (BigNum*)number;        
    }   

    // Sumo los primeros numeros hasta que termino el numero corto
    for(int i = 0; i< corto; i++){
        int parcial = 0;
        parcial = carry + n_largo->digits[i] + n_corto->digits[i];
        if(parcial >= 10){
            parcial-=10;
            carry = 1;
        }else{
            carry = 0;
        }
        //cout << "Sumo: "<< n_largo->digits[i] << " + carry + " << n_corto->digits[i] << " = " << parcial << " + carry= "<< carry*10 << endl;
        resultado[i] = parcial;
    }

    // Sumo los numeros del numero largo con cero
    for(int k = corto;k < largo; k++){
        int parcial = 0;
        parcial = carry + n_largo->digits[k];
        if(parcial >= 10){
            parcial-=10;
            carry = 1;
        }else{
            carry = 0;
        }        
        //cout << "Sumo: "<< n_largo->digits[k] << " + 0 = "  << parcial << " + carry= "<< carry*10 << endl;
        resultado[k] = parcial;
        
    }
    // Sumo el ultimo carry
    if(carry){
        resultado[largo] = carry;
        largo++;
    }
    
    //cout << "Sumo: " << resultado[largo] << endl;
    n_largo = NULL;
    n_corto = NULL; 
    resul->digits = resultado;
    resul->longitud = largo;
    resul->signo = signo; 
    resul->valid_num = true;
}

BigNum* BigNum::resta(BigNum* number){
    return number;
}

BigNum BigNum::multiplicacion(const BigNum* number){
    int arriba = max(longitud, number->longitud);
    int abajo = min(longitud, number->longitud);
    int largo = arriba + abajo + 1;
    unsigned short int* resultado = new unsigned short int[largo];
    BigNum n_resultado(resultado, largo, 0);
    n_resultado.digits = resultado; 
    n_resultado.longitud = largo;
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
        int carry = 0;
        unsigned short int* resultado_parcial = new unsigned short int[largo];
        for(int k = 0; k < arriba; k++){
            int parcial = n_abajo->digits[i] * n_arriba->digits[k];
            if(parcial >= 10){
                carry = parcial / 10;
                parcial = parcial - (carry * 10);
            }else{
                carry = 0;
            }       
            // en resultado esta la multiplicacion del elemento i con todo el vector "arriba"
            // la "i" indica el desplazamiento por la posicion del num de abajo.
            resultado_parcial[k + i] += parcial;
            if(resultado_parcial[k + i] >= 10){
                resultado_parcial[k + i] -= 10;
                carry++;
            }
            resultado_parcial[k + 1 + i] = carry;
            //cout << n_abajo->digits[i] << " * " << n_arriba->digits[k] << " = " << resultado_parcial[k+i] << endl;
            
        }
        //cout << "--- ";
        // Sumo el resultado obtenido previamente con el acumulado.
        // necesito un vector que me acumule las sumas previas 
        // necesito sumar el acumulado con resultado_parcial
        BigNum resultado_parc(resultado_parcial, largo, 0);
        resultado_parc.suma(&n_resultado, &n_resultado);        // esto esta bien?? le paso el mismo numero pero uno es const y el otro no y me deja
        for(int j = 0; j < largo; j++){
            cout << resultado_parcial[arriba + abajo - j];
        }
        cout << endl;
    }
    cout << n_resultado;
    // asigno signo a resultado
    if(n_arriba->signo == n_abajo->signo) n_resultado.signo = 0;
    else n_resultado.signo = 1;
    
    return n_resultado;
}

int BigNum::get_sign(){
    return signo;
}

bool BigNum::get_valid_num(){
    return valid_num;
}
void BigNum::set_sign(int s){
    signo = s;
}
void BigNum::mostrar()
{
    if(digits)
    {
        cout << "El número almacenado tiene signo " << signo << " y es el: ";
        for (int i = 0; i < longitud; i++) {
            cout << digits[longitud - 1 - i];
        }
        cout << endl;
    }
    else
        cout<<"NAN"<<endl;
}

BigNum::~BigNum()
{
    if(digits)
        delete [] digits;
} 

// --------------------------------------------------------------
//                      Sobrecarga de operadores
//
// Sobrecarga del operador +
BigNum operator + (const BigNum &p1, const BigNum &p2)
{
    int carry = 0;
    int largo = max(p1.longitud, p2.longitud);
    int corto = min(p1.longitud, p2.longitud);
    unsigned short int* resultado = new unsigned short int[largo + 1]; 
    BigNum n_largo, n_corto, resul;

    // distingo por el largo de los numeros
    if(corto == p2.longitud){
        n_largo.copiarBigNum(p1);
        n_corto.copiarBigNum(p2);
    }else{
        n_largo.copiarBigNum(p2);
        n_corto.copiarBigNum(p2);        
    }   

    // Sumo los primeros numeros hasta que termino el numero corto
    for(int i = 0; i< corto; i++){
        int parcial = 0;
        parcial = carry + n_largo.digits[i] + n_corto.digits[i];
        if(parcial >= 10){
            parcial-=10;
            carry = 1;
        }else{
            carry = 0;
        }
        //cout << "Sumo: "<< n_largo->digits[i] << " + carry + " << n_corto->digits[i] << " = " << parcial << " + carry= "<< carry*10 << endl;
        resultado[i] = parcial;
    }

    // Sumo los numeros del numero largo con cero
    for(int k = corto;k < largo; k++){
        int parcial = 0;
        parcial = carry + n_largo.digits[k];
        if(parcial >= 10){
            parcial-=10;
            carry = 1;
        }else{
            carry = 0;
        }        
        //cout << "Sumo: "<< n_largo->digits[k] << " + 0 = "  << parcial << " + carry= "<< carry*10 << endl;
        resultado[k] = parcial;
        
    }
    // Sumo el ultimo carry
    if(carry){
        resultado[largo] = carry;
        largo++;
    }
    
    //cout << "Sumo: " << resultado[largo] << endl;
    resul.digits = resultado;
    resul.longitud = largo;
    resul.signo = p1.signo; 
    resul.valid_num = true;
    return resul;
}


// Sobrecarga del operador -
BigNum operator - (const BigNum &p1, const BigNum &p2){
    return p1;
}

// Sobrecarga del operador *
BigNum operator * (const BigNum &p1, const BigNum &p2){
    int arriba = max(p1.longitud, p2.longitud);
    int abajo = min(p1.longitud, p2.longitud);
    int largo = arriba + abajo + 1;
    unsigned short int* resultado = new unsigned short int[largo];
    for(int i = 0; i<largo; i++)
        resultado[i] = 0;
    BigNum n_resultado(resultado, largo, 0);
    n_resultado.digits = resultado; 
    n_resultado.longitud = largo;
    BigNum n_arriba, n_abajo; 

    if(abajo == p1.longitud){
        n_arriba.copiarBigNum(p2);
        n_abajo.copiarBigNum(p1); 
    }else{
        n_arriba.copiarBigNum(p1);
        n_abajo.copiarBigNum(p2);        
    } 
    // aca comienza la multiplicacion
    for(int i = 0; i < abajo; i++){
        int carry = 0;
        unsigned short int* resultado_parcial = new unsigned short int[largo];
        for(int k = 0; k < arriba; k++){
            int parcial = n_abajo.digits[i] * n_arriba.digits[k];
            if(parcial >= 10){
                carry = parcial / 10;
                parcial = parcial - (carry * 10);
            }else{
                carry = 0;
            }       
            // en resultado esta la multiplicacion del elemento i con todo el vector "arriba"
            // la "i" indica el desplazamiento por la posicion del num de abajo.
            resultado_parcial[k + i] += parcial;
            if(resultado_parcial[k + i] >= 10){
                resultado_parcial[k + i] -= 10;
                carry++;
            }
            resultado_parcial[k + 1 + i] = carry;
            //cout << n_abajo->digits[i] << " * " << n_arriba->digits[k] << " = " << resultado_parcial[k+i] << endl;
            
        }
        //cout << "--- ";
        // Sumo el resultado obtenido previamente con el acumulado.
        // necesito un vector que me acumule las sumas previas 
        // necesito sumar el acumulado con resultado_parcial
        BigNum resultado_parc(resultado_parcial, largo, 0);
        n_resultado = n_resultado + resultado_parc;
        for(int j = 0; j < largo; j++){
            cout << resultado_parcial[arriba + abajo - j];
        }
        cout << endl;
    }
    cout << n_resultado;
    // asigno signo a resultado
    if(n_arriba.signo == n_abajo.signo) 
        n_resultado.signo = 0;
    else n_resultado.signo = 1;
    
    return n_resultado;
}

bool operator==(const BigNum &p1, const BigNum &p2)
{
    if(!p1.valid_num || !p2.valid_num)
        return false;
    if(p1.digits == NULL || p2.digits == NULL)
        return false;
    if(p1.longitud != p2.longitud || p1.signo != p2.signo)
        return false;
    for(int i = 0; i < p1.longitud; i++)
    {
        if(p1.digits[i] != p2.digits[i])
            return false;
    }
    return true;
}

BigNum & BigNum::operator=(const BigNum &orig)
{
    if((*this) == orig)
        return *this;
    (*this).copiarBigNum(orig);
    return *this;
}

ostream& operator << (ostream& os, const BigNum &dt)
{
    if(dt.valid_num == false)
    {
        os<<"-- No es un número --"<<endl;
        return os;
    }
    os<<"El número almacenado tiene signo "<<dt.signo<<" y es el: ";
    int imprimir = min(dt.precision, dt.longitud);
    for (int i = 0; i < imprimir; i++) {
        cout << dt.digits[imprimir - 1 - i];
    }
    os << endl;
    return os;
}

void BigNum::copiarBigNum(const BigNum &orig)
{
    if(digits)
        delete [] digits;
    precision = orig.precision;
    signo = orig.signo;
    longitud = orig.longitud;
    valid_num = orig.valid_num;
    if(orig.digits)
    {
        int l = orig.longitud;
        digits = new unsigned short int[l];
        for(int i = 0; i < l; i++)
            digits[i] = orig.digits[i];
    }
    else
        digits = NULL;
}
