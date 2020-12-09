read: read.o
	gcc -o main read.c

clean:
	rm *.o
	rm main

run:
	./main
