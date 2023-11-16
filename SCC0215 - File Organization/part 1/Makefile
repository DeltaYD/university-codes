# Makefile

all: programaTrab

matriz: main.o funcoesFile.o
	gcc -o matriz main.o funcoesFile.o

main.o: main.c funcoesFile.h
	gcc -o main.o main.c -c -Wall

grafos.o: funcoesFile.c funcoesFile.h
	gcc -o funcoesFile.o funcoesFile.c -c -Wall

run: all
	./programaTrab