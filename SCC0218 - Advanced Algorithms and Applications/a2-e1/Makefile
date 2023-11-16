all: mainCoin.o
	gcc -g mainCoin.o CoinAlg.o -o main

mainCoin.o: mainCoin.c CoinAlg.o
	gcc -g -c -Wall mainCoin.c 

CoinAlg.o: CoinAlg.c CoinAlg.h
	gcc -g -c -Wall CoinAlg.c 

clean:
	rm -f mainCoin.o CoinAlg.o

run: all
	./main