
//快速排序是对冒泡法排序的一种改进。
#include <stdio.h>
#include <stdlib.h>
#define N 9

int partition(int a[], int low, int high){
	
	int key;
	key = a[low];
	
	while(low < high){
		while(low < high && a[high] >= key)
			high--;
		if(low < high)
			a[low++] = a[high];
			
		while( low < high && a[low] <= key)
			low++;
		if(low < high)
			a[high--] = a[low];
	}
	a[low] = key;
	return low;
}

void QuickSort(int a[], int start, int end){
	
	int index;
	if (start < end){
		
		index = partition(a, start, end);
		QuickSort(a, start, index-1);
		QuickSort(a, index+1, end);
	}
	return;
}

int main(void){
	
	int i;
	int arr[N] = {32, 12, 7, 78, 23, 45, 2, 9, 16};
	
	printf("排序前:\n");
	for(i = 0; i < N; i++)
		printf("%d ", arr[i]);
		
	QuickSort(arr, 0, N-1);
	
	printf("\n排序后:\n");
	for(i = 0; i < N; i++)
		printf("%d ", arr[i]);
		
	printf("\n");
	return 0;
}