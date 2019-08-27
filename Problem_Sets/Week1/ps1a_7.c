#include<stdio.h>
#define M 5
#define N 12
#define P 19

int max(int a, int b, int c){

	int d = a * (a >= b) + b * (a < b);
	return c * (c >= d) + d * (c < d);
}

int main(){

	int _MAX = max(M, N, P);
	printf("MAX = %d.\n", _MAX);
}
