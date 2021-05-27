CXXARGS  = -g -Wall -ansi -std=c++17
CXXFLAGS = -I. $(CXXARGS) -g

all: main
	

main: main.o cmdline.o bignum.o calculadora.o utils.o _error.o
	$(CXX) $(CXXFLAGS) -o main bignum.o calculadora.o cmdline.o main.o utils.o _error.o 

main.o: main.cpp cmdline.h calculadora.h bignum.h utils.h _error.h
	$(CXX) $(CXXFLAGS) -c main.cpp

cmdline.o: cmdline.cc cmdline.h
	$(CXX) $(CXXFLAGS) -c cmdline.cc

calculadora.o: calculadora.cpp calculadora.h 
	$(CXX) $(CXXFLAGS) -c calculadora.cpp

bignum.o: bignum.cpp bignum.h
	$(CXX) $(CXXFLAGS) -c bignum.cpp

utils.o: utils.cpp utils.h
	$(CXX) $(CXXFLAGS) -c utils.cpp

_error.o: _error.cpp _error.h
	$(CXX) $(CXXFLAGS) -c _error.cpp	

test-fine: main
	@set -e;
	@echo Archivos de prueba: entrada1 salida1 salida1ref con precisión 20.;
	@./main -i entrada1.txt -o salida1.txt -p 20;
	@echo Probando si el archivo de salida es correcto..;
	@diff -b salida1ref.txt salida1.txt >/dev/null 2>&1; 
	@echo Test ok.;
	@echo -------------------------------------------------------------------------------;

test-valgrind-fine: main
	@set -e;
	@echo Archivos de prueba: entrada1 salida1 salida1ref con precisión 20.;
	@echo Probando si hubieron fugas de memoria..;
	@valgrind --tool=memcheck ./main -i entrada1.txt -o salida1.txt -p 20 2>/dev/null;
	@echo Test ok;
	@echo -------------------------------------------------------------------------------;


test-wrong: main
	@set -e;
	@echo Archivo de prueba: entrada2, tiene mal el formato.;
	@./main -i entrada2.txt -o entrada2.txt -p 1;
	@echo Test ok.;
	@echo -------------------------------------------------------------------------------;

test-valgrind-wrong: main
	@set -e;
	@echo Archivo de prueba: entrada2, tiene mal el formato.;
	@echo Probando si hubieron fugas de memoria..;
	@valgrind --tool=memcheck ./main -i entrada2.txt -o entrada2.txt -p 1 2>/dev/null;
	@echo Test ok.;
	@echo -------------------------------------------------------------------------------;

clean:
	$(RM) -vf *.o *.t *.out *.err main
