#include <stdio.h>

#define MAX 4

void collatz(int n){
	
	printf("%d\n", n);

	while (n != 1) {

		if (n % 2 == 0) {

			n = n / 2;
		} else {
			n = 3*n + 1;
		}
	printf("%d\n", n);
	}
}

int main(){

	int fib[MAX] = {1,1};

	for(int i = 2; i < MAX; i++){
	
		fib[i] = fib[i-1] + fib[i-2];
	}
	for(int j = 0; j < MAX; j++){

		printf("Fib[%d] = %d\n", j+1, fib[j]);
		collatz(fib[j]);
	}
	return 0;
}
