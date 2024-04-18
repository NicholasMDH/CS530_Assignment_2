asxe : main.o Pass1.o Pass2.o
	g++ -g -Wall -std=c++11 main.o Pass1.o Pass2.o -o asxe

asxe.o : main.cpp Pass1.cpp Pass2.cpp Assembler.h
	g++ -g -c -Wall -std=c++11 main.cpp Pass1.cpp Pass2.cpp asxe.cpp

clean:
	rm *.o asxe