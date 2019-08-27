CC = gcc

main: ps1b_2.c Stack.o
	$(CC) ps1b_2.c Stack.o -o main

Stack.o: Stack.c
	$(CC) -c Stack.c

clean:
	rm *.o main