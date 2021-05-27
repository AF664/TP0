CCFLAGS= -Wall -ansi -pedantic -std=c++17 -g
CC= c++
all: main

main: main.o calculadora.o bignum.o utils.o _error.o cmdline.o
	$(CC) $(CCFLAGS) -o calculadora.exe main.o calculadora.o bignum.o utils.o _error.o cmdline.o

main.o: main.cpp calculadora.h bignum.h utils.h _error.h cmdline.h
	$(CC) $(CCFLAGS)  -o main.o -c main.cpp

calculadora.o: calculadora.cpp  bignum.h utils.h _error.h 
	$(CC) $(CCFLAGS) -o calculadora.o -c calculadora.cpp

bignum.o: bignum.cpp utils.h _error.h 
	$(CC) $(CCFLAGS) -o bignum.o -c bignum.cpp

utils.o: utils.cpp 
	$(CC) $(CCFLAGS) -o utils.o -c utils.cpp

cmdline.o: cmdline.cc
	$(CC) $(CCFLAGS) -o cmdline.o -c cmdline.cc

