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

clean:
	$(RM) -vf *.o *.t *.out *.err main
