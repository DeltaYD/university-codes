all: main.o
	gcc -g main.o stableMatchingFile.o -o main

main.o: main.c stableMatchingFile.o
	gcc -g -c -Wall main.c 

stableMatchingFile.o: stableMatchingFile.c stableMatchingFile.h
	gcc -g -c -Wall stableMatchingFile.c 

clean:
	rm -f main.o stableMatchingFile.o

run: all
	./main