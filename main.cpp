#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <string>
#include "calculadora.h"
#include "big_num.h"
#include "cmdline.h"

// los agrego para el debug

#include "calculadora.cpp"
#include "big_num.cpp"
#include "cmdline.cpp"

// En este header ponemos todas las declaraciones que no podemos agrupar
// en ninguna clase
#include "utils.h" 

using namespace std;

enum codigo_error{ENTRADA,SALIDA};

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_precision(string const &);
static void opt_help(string const &);

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "p", "precision", NULL, opt_precision, OPT_DEFAULT}, // OPT_MANDATORY
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

#define DEFAULT_PRECISION 20

static int precision = DEFAULT_PRECISION;
static istream *iss = 0;
static ostream *oss = 0;
static fstream ifs;
static fstream ofs;

static void opt_input(string const &arg){
	// Si el nombre del archivos es "-", usaremos la entrada
	// estándar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		iss = &cin;
	} else {
		ifs.open(arg.c_str(), ios::in);
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void opt_output(string const &arg){
	// Si el nombre del archivos es "-", usaremos la salida
	// estándar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void opt_precision(string const &arg){

	istringstream iss(arg);
	
	// Intentamos extraer el precision de la línea de comandos.
	// Para detectar argumentos que únicamente consistan de 
	// números enteros, vamos a verificar que EOF llegue justo
	// después de la lectura exitosa del escalar.
	//
	if (!(iss >> precision)
	    || !iss.eof()) {
		cerr << "non-integer precision: "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}

	if (iss.bad()) {
		cerr << "cannot read integer precision."
		     << endl;
		exit(1);
	}
}

static void opt_help(string const &arg){
	cout << "cmdline -p precision [-i file] [-o file]"
	     << endl;
	exit(0);
}


int main(int argc,char *const argv[])
{  
    string linea;
    cmdline comandos(options);
    comandos.parse(argc, argv);

    while(getline(*iss, linea))
    {
        cout<<"--  Defino calculadora  --"<<endl;
        calculadora cuenta(linea, precision);
        cout<<"--  Resolver  --"<<endl;
        *oss<<cuenta.resolver();
        cout<<"--   Fin del calculo   --"<<endl;
        if(oss->bad()) 
            exit(1);
        if(iss->bad())
            exit(1);
        cout<<"--  Fin de linea  --"<<endl;
    }
    return 0;

}