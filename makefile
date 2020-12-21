main: main.o
	gcc main.c parse.h parse.c -o main

run:
	./main