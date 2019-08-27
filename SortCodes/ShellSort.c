
//希尔排序，也称递减增量排序算法，是插入排序的一种更高效的改进版本。希尔排序是非稳定排序算法。
#include<stdio.h>

//希尔排序, 按从小到大排序
void ShellSort(int arr[], int n){
	
	int i, j, k;
	int temp, gap;
	
	//步长的选取
	for (gap = n / 2; gap > 0; gap /= 2){
		//直接插入排序原理
		for (i = 0; i < gap; i++){
			//每次加上步长，即按列排序。
			for (j = i + gap; j < n; j += gap)
			
				if (arr[j] < arr[j - gap]){
					
					temp = arr[j];
					k = j - gap;
					//记录后移，查找插入位置
					while (k >= 0 && arr[k] > temp){
						
						arr[k + gap] = arr[k];
						k -= gap;
					}
					arr[k + gap] = temp; //找到位置插入
				}
		}
	}
}

// 打印结果
void Show(int arr[], int n){
	
	int i;
	for ( i = 0; i < n; i++ )
		printf("%d  ", arr[i]);
	printf("\n");
}

int main(){   
	
	//测试数据
	int array[10] = { 8, 4, 2, 3, 5, 1, 6, 9, 0, 7 };
	
	//排序前数组序列
	Show(array, 10 );
	
	ShellSort(array, 10 );
	
	//排序后数组序列
	Show(array, 10 );
	return 0;
}