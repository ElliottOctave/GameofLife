

all: main.o GUI.o Procedures.o
	gcc main.o GUI.o Procedures.o -lSDL2 -o main

main.o: main.c GUI.h Procedures.h
	gcc -c main.c -o main.o

GUI.o: GUI.c GUI.h Procedures.h
	gcc -c GUI.c -o GUI.o

Procedures.o: Procedures.c Procedures.h
	gcc -c Procedures.c -o Procedures.o



