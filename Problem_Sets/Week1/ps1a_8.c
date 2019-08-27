
#include <stdio.h>
#define SIZE 250

void InsertionSort(int array[], int n){ 
	
	int i;
	for (i = 1; i < n; i++){
		
		int element = array[i];
		int j = i-1;
		
		while (j >= 0 && array[j] > element){
			
			array[j+1] = array[j];
			j--; 
		}
		
	array[j+1] = element;
	}
}

int main(void){
	
	int numbers[SIZE]; 
	int i, n = 0;
	int flag = 1, rev;

	while (flag){ // Initialize the array numbers[] by receiving integers from keyboard
	
		if (n == SIZE-1) 
			break;
		printf("Type in a number:\n"); 
		
		rev = scanf("%d", &numbers[n]); 
		printf("numbers[%d] = %d\n", n, numbers[n]); 
		
		if (rev <= 0) // not an integer
			flag = 0; 
		else 
			n++;
}
	InsertionSort(numbers, n); 
	
	for (i = 0; i < n; i++)
		printf("%d\n", numbers[i]);
		
	return 0; 
}