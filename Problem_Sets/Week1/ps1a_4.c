#include<stdio.h>
#define N 15

void collatz(int n){
	
	printf("%d\n", n);

	while (n != 1){

		if (n%2 == 0){
	
			n /= 2;
		}else{

			n = 3*n + 1;
		}
		printf("%d\n", n);
	}
}

int main(){

	collatz(N);

	return 0;
}
