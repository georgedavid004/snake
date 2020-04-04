all:functions.o main.o  a.out
functions.o:functions.cc Matrix.h
	g++ -std=c++11 functions.cc -g -c 
main.o:main.cc Matrix.h
	g++ -std=c++11 main.cc -g -c
a.out:functions.o main.o
	g++ -std=c++11 main.o functions.o -g 
clear:
	rm *.o *.gch *.out
