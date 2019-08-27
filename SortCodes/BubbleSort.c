
#include<stdio.h>

void BubbleSort(int a[], int len ){

	int i, j, temp;

	for (i = 0; i < len - 1; i++)
		for (j = 0; j < len - 1 - i; j++)
			if (a[j] > a[j+1]){
			
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
}

int main(){

	int i;
	int a[] = {3, 7, 4, 9, 6, 1, 8, 16, 32, 2, 10};
	int len = (int) sizeof(a)/sizeof(*a);

	BubbleSort(a, len);

	for (i = 0; i < len; i++){
	
		printf("%d ", a[i]);
	}
	putchar('\n');
	return 0;
}
