all: main.o parse.o
	gcc -o main main.o parse.o

main.o: main.c parse.h
	gcc -c main.c

parse.o: parse.c parse.h
	gcc -c parse.c

run:
	./main

clean:
	rm *.o
	rm main
