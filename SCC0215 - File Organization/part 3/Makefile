all: programaTrab.o
	gcc -g programaTrab.o funcoesFile.o -o programaTrab

programaTrab.o: programaTrab.c funcoesFile.o
	gcc -g -c -Wall programaTrab.c 

funcoesFile.o: funcoesFile.c funcoesFile.h
	gcc -g -c -Wall funcoesFile.c 


clean:
	rm -f programaTrab.o funcoesFile.o

run: all
	./programaTrab