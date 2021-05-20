CXXARGS  = -g -Wall -ansi
CXXFLAGS = -I. $(CXXARGS)

all: main
	

main: main.o cmdline.o big_num.o cmdline.o big_num.o calculadora.o
	$(CXX) $(CXXFLAGS) -o main big_num.o calculadora.o cmdline.o main.o

main.o: main.cpp cmdline.h calculadora.h big_num.h
	$(CXX) $(CXXFLAGS) -c main.cpp

cmdline.o: cmdline.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c cmdline.cpp

calculadora.o: calculadora.cpp calculadora.h big_num.h
	$(CXX) $(CXXFLAGS) -c calculadora.cpp

big_num.o: big_num.cpp big_num.h
	$(CXX) $(CXXFLAGS) -c big_num.cpp

clean:
	$(RM) -vf *.o *.t *.out *.err
