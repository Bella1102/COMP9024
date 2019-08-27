#include<stdio.h>
#define N 3

float innerProduct(float a[], float b[], int n){

	int i;
	float product = 0.0;

	for(i = 0; i < n; i++){
	
		product += a[i]*b[i];
	}
	return product;
}

int main(){

	float a[N] = {1, 2, 3};
	float b[N] = {4, 5, 6};
	
	float res = innerProduct(a, b, N);
	printf("The result is: %5.1f.\n", res);

	return 0;
}
