#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int main(int argc, char *argv[]){

	if (argc != 2){
	
		printf("Wrong Input.");
		return 1;
	}

	int n = atoi(argv[1]);
	
	if (n > 0){

		unsigned long long int *arr = malloc(sizeof(unsigned long long int) * n);
		arr[0] = 1;
		arr[1] = 1;

		for (int i = 2; i < n; i++){
		
			arr[i] = arr[i-1] + arr[i-2];
		}
		printf("%lld\n", arr[n-1]);

	free(arr);
	}
	return 0;

}
