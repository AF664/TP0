#include <iostream>
#include <string>
#include "calculadora.h"
#include "cmdline.h"

// En este header ponemos todas las declaraciones que no podemos agrupar
// en ninguna clase
#include "utils.h" 

using namespace std;

/* En esta parte declaro las funciones que va usar la variable de configuracion
de acuerdo a la opcion de entrada.*/
// Abre el flujo de entrada segun el nombre de archivo, o stdin por defecto
static void flujo_entrada(string const &nombre_archivo);

// Abre el flujo de salida segun el nombre de archivo, o stdout por defecto
static void flujo_salida(string const &nombre_archivo);

// Imprime mensaje de error, con mensaje adicional en msj_adic en caso que
// se requiera (o null e imprime mensaje error estandar)
static void imprimir_ayuda(string const &msj_adic);

static void opt_precision(string const &precision);

// Devuelve un mensaje de error de acuerdo al código de entrada, y retorna 
// un valor distinto de cero al sistema operativo.
void error(int codigo);

enum codigo_error{ENTRADA,SALIDA};

#define PRECISION_DEFAULT "20"



option_t config[] = {
    {1, "i", "input","-", flujo_entrada, OPT_DEFAULT},
    {1, "o", "output","-", flujo_salida, OPT_DEFAULT},
    {1, "p", "precision",PRECISION_DEFAULT,opt_precision, OPT_DEFAULT},
    {0, "h", "help",nullptr,imprimir_ayuda, OPT_DEFAULT},
    {0,},// Fin de opciones

};


static int precision;
static istream *iss = 0;
static ostream *oss = 0;
static fstream ifs;
static fstream ofs;

int main(int argc,char *const argv[])
{  
    string linea;
    cmdline comandos(config);
    comandos.parse(argc, argv);

    while( !(iss->eof()) )
    {
        getline(*iss,linea);
        calculadora cuenta(linea);
        *oss<< resultado(cuenta);
        if( oss->bad()) 
            error(SALIDA);
        if(iss->bad())
            error(ENTRADA);

    }
    return 0;


}