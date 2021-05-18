#include <iostream>
#include <string>
#include "big_num.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>

#include "cmdline.h"

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_precision(string const &);
static void opt_help(string const &);
void calculadora();

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "p", "precision", NULL, opt_precision, OPT_DEFAULT}, // OPT_MANDATORY
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static int precision;
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

void calculadora(istream *is, ostream *os){
	string linea;

	// aca se toman los numeros y se realizan las operaciones 
	while (getline(*is,linea)) {
		string numero1[linea.length()], numero2[linea.length()];
		char data;				// 
		char operacion;			// buscamos que operacion tiene la linea
		bool valida = true;		// verificamos si es una linea valida
		bool num = false;		// num = false (para primer numero) num = true (para seg numero)	
		int i = 0;
		istringstream iss(linea);// leo la linea como "istringstream" para solo tener 
		while(iss){
			if(iss >> data){
				// hasta aca lee las lineas individualmente sin espacio o tab 
				//     -8675645    * + 876  --> -8675645*+876
				// falta separar en numeros y operacion
				// guardo siempre el primer valor a numero 1 (si es o no un signo)
				if(i == 0 && num == false){
					numero1[i] = data;
					i++;
				}else{
					// Guardo primer numero
					if(num == false){
						// cuando data == * || + || - deja de ser numero 1
						if(!isdigit(data)){
							num = true;
							numero1[i] = '\0';
							i = 0;
						}else{
							// guardo en numero1
							numero1[i] = data;
							i++;
						}
					}
					// Guardo la operacion y el segundo numero
					if(num == true){
						// aca esta el operando en el primer caracter
						if(i == 0) operacion = data;
						// guardo en numero2
						// lo deberia guardar siempre
						// de ahi en adelante guardo hasta final de la linea
						else{
							// todos los demas numeros
							if(!isdigit(data)){
								numero2[i-1] = '\0';
								i = 0;
							}else{
								// guardo en numero2
								numero2[i-1] = data;
							}							
						}
						i++;
					}
				}
			}
		}
		// Aca se 
		cout << endl << "Fin de linea" << endl;
		// Contamos el numero de signos y si existe algun caracter no valido.
		
	}
	// Manejo de errores.
	if (os->bad()) {
		cerr << "cannot write to output stream."
		     << endl;
		exit(1);
	}
	if (is->bad()) {
		cerr << "cannot read from input stream."
		     << endl;
		exit(1);
	}
	if (!is->eof()) {
		cerr << "cannot find EOF on input stream."
		     << endl;
		exit(1);
	}
}
	

int main(int argc, char *argv[]){

	cmdline cmdl(options);
	cmdl.parse(argc, argv);
	calculadora(iss, oss);
    string numero = "56";
    string numero2 = "-511";
    BigNum num(numero,90); 
    BigNum num2(numero2,90); 
    //BigNum* resultado = num.suma(&num2);
    BigNum* resultado = num.multiplicacion(&num2);
    cout << *resultado;
    return 0;
}
