
output: wordchains.o additional.o
	gcc wordchains.o additional.o -o output

wordchains.o: wordchains.c
	gcc -c wordchains.c
	
additional.o: additional.c additional.h
	gcc -c additional.c additional.h

clean:
	rm *.o output
