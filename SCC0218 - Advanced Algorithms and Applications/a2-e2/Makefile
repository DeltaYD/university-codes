all: mainStationBalance.o
	gcc -g mainStationBalance.o StationBalance.o -o main

mainStationBalance.o: mainStationBalance.c StationBalance.o
	gcc -g -c -Wall mainStationBalance.c 

StationBalance.o: StationBalance.c StationBalance.h
	gcc -g -c -Wall StationBalance.c 

clean:
	rm -f mainStationBalance.o StationBalance.o

run: all
	./main