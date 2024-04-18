asxe : main.o Pass1.o Pass2.o Assembler.o
	g++ -g -Wall -std=c++11 main.o Pass1.o Pass2.o Assembler.o -o asxe

asxe.o : main.cpp Pass1.cpp Pass2.cpp Assembler.h Assembler.cpp
	g++ -g -c -Wall -std=c++11 main.cpp Pass1.cpp Pass2.cpp Assembler.cpp asxe.cpp

clean:
	rm *.o asxe P2sample.temp P2sample.lis