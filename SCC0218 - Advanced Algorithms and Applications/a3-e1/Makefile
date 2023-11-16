all: mainCdTracks.o
	gcc -g mainCdTracks.o CdTracks.o -o main

mainCdTracks.o: mainCdTracks.c CdTracks.o
	gcc -g -c -Wall mainCdTracks.c 

CdTracks.o: CdTracks.c CdTracks.h
	gcc -g -c -Wall CdTracks.c 

clean:
	rm -f mainCdTracks.o CdTracks.o

run: all
	./main