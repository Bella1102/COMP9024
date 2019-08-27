
#include<stdio.h>
#include<stdlib.h>
#include "IntStack.h"

int main(int argc, char *argv[]){

	int n;

	StackInit();

	if (argc != 2){
	
		printf("Usage: %s number\n", argv[0]);
		return 1;
	}
	n = atoi(argv[1]);

	while (n > 0){
	
		StackPush(n%2);
		n /= 2;
	}

	while(!StackIsEmpty()){
	
		printf("%d", StackPop());
	}
	putchar('\n');

	return 0;
}
