
CC = gcc
Other = -Wall -Werror 

binary: binary.o IntStack.o
	$(CC) -o binary binary.o IntStack.o

binary.o: binary.c
	$(CC) $(Other) -c binary.c

IntStack.o: IntStack.c
	$(CC) $(Other) -c IntStack.c

clean:
	rm *.o binary