
#include<stdio.h>

void swap(int *a, int *b){

	int temp = *a;
	*a = *b;
	*b = temp;
}

void SelectionSort(int a[], int len){

	int i,j;
	// 进行len-1轮选择
	for(i = 0; i < len - 1; i++){
	
		int min_index = i;
		// 找出第i小的数所在的位置
		for(j = i + 1; j < len; j++){
		
			if (a[j] < a[min_index]){
			
				min_index = j;
			}
		}

		// 将第i小的数，放在第i个位置，如果刚好，就不用交换
		if (i != min_index){

			swap(&a[min_index], &a[i]);
		}
	}
}

int main(){

	int num[] = {3,6,9,2,5,8,1,4,7};
	int len = (int)sizeof(num)/sizeof(*num);

	SelectionSort(num, len);
	for(int i = 0; i < len; i++){
	
		printf("%d ", num[i]);
	}
	putchar('\n');

	return 0;
}
