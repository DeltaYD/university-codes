all: mainRat.o
	gcc -g mainRat.o Rat.o -o main

mainRat.o: mainRat.c Rat.o
	gcc -g -c -Wall mainRat.c 

Rat.o: Rat.c Rat.h
	gcc -g -c -Wall Rat.c 

clean:
	rm -f mainRats.o Rat.o

run: all
	./main