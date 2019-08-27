#include <stdio.h> 

#define M 4
#define N 4 
#define P 4

// Function matrixProduct computes a[][]*b[][], and stores the result in c[][]

void matrixProduct(float a[M][N], float b[N][P], float c[M][P]) {
	
	int i,j,k;
	
	for(i = 0; i < M; i++){
		for(j = 0; j < P; j++){
		
			c[i][j] = 0.0;
			for (k = 0; k < N; k++){
			
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}

int main(){

	float a[M][N] = { {1, 1, 1, 1}, {2, 2, 2, 2}, {3, 3, 3, 3}, {4, 4, 4, 4}}; 
	float b[N][P] = { {1, 1, 1, 1}, {2, 2, 2, 2}, {3, 3, 3, 3}, {4, 4, 4, 4}}; 
	float c[M][P]; // To store result

	int i, j;
	matrixProduct(a, b, c);
	
	printf("Result matrix is:\n");
	for (i = 0; i < M; i++){
	
		for(j = 0; j < P; j++){
		
			printf("%4.1f\t",c[i][j]);
		}
		printf("\n");
	}
	return 0;
}
