
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NUM 10000

// This template is only a guide 
// You need to include additional fields, data structures and functions  

// data type for heap nodes
// each node stores the priority (key), name, execution time, release time and deadline of one task
typedef struct HeapNode { 
	
	int key; 		// key of this task
	int TaskName;  	// task name 
	int Etime; 		// execution time of this task
	int Rtime; 		// release time of this task
	int Dline; 		// deadline of this task

	int degree;
	struct HeapNode *child;
	struct HeapNode *sibling;
	struct HeapNode *parent;

} HeapNode;

// data type for a priority queue (heap) 
// this is heap header
typedef struct BinomialHeap {

	int  size; 		 // count of items in the heap
	HeapNode *head;  

} BinomialHeap;

// create a new heap node to store an item (task) 
// k:key, n:task name, c: execution time, r:release time, d:deadline
// ... you need to define other parameters yourself) 	
HeapNode *newHeapNode(int k, int n, int c, int r, int d) { 
	 
	HeapNode *new;
	new = malloc(sizeof(HeapNode));
	assert(new != NULL);
	new->key = k;
	new->TaskName = n;
	new->Etime = c;
	new->Rtime = r; 
	new->Dline = d;

	new->degree = 0;
	new->child = NULL;
	new->sibling = NULL;
	new->parent = NULL;

	return new;
}

// create a new empty heap-based priority queue
// this function creates an empty binomial heap-based priority queue
BinomialHeap *newHeap(){ 
	
	BinomialHeap *T;
	T = malloc(sizeof(BinomialHeap));
	assert (T != NULL);
	
	T->head = NULL;
	T->size = 0;		// initialise all the fields here

	return T;
}

HeapNode *heapMerge(BinomialHeap *heap1, BinomialHeap *heap2);
HeapNode *heapUnion(BinomialHeap *heap1, BinomialHeap *heap2);
void heapRemove(BinomialHeap *heap, HeapNode *head1, HeapNode *head2);
void Insert(BinomialHeap *T, int k, int n, int c, int r, int d);
HeapNode *RemoveMin(BinomialHeap *T);
int Min(BinomialHeap *T);

// auxiliary function 1
// 将heap1, heap2中的根链表合并成一个按度数递增的链表，返回合并后的head节点
// Time complexity: O(log n)
HeapNode *heapMerge(BinomialHeap *heap1, BinomialHeap *heap2) {

	if(heap1->head == NULL) return heap2->head;
	if(heap2->head == NULL) return heap1->head;

	HeapNode *newhead, *tail;
	HeapNode *h1 = heap1->head;
	HeapNode *h2 = heap2->head;

	if(heap1->head->degree <= heap2->head->degree) {

		newhead = heap1->head;
		h1 = h1->sibling;
	}
	else {
		newhead = heap2->head;
		h2 = h2->sibling;
	}
	tail = newhead;
	while(h1 != NULL && h2 != NULL) {

		if(h1->degree <= h2->degree) {
			tail->sibling = h1;
			h1 = h1->sibling;
		}
		else {
			tail->sibling = h2;
			h2 = h2->sibling;
		}
		tail = tail->sibling;
	}
	tail->sibling = (h1 != NULL) ? h1 : h2;
	
	return newhead;
}

// auxiliary function 2
// 合并二项堆：将heap1, heap2合并成一个堆，并返回合并后的堆
// Time complexity: O(log n)
HeapNode *heapUnion(BinomialHeap *heap1, BinomialHeap *heap2) {

	HeapNode *newhead = heapMerge(heap1, heap2);
	heap1->head = NULL;
	heap2->head = NULL;

	if (newhead == NULL) {
		return NULL;
	}

	HeapNode *prev = NULL;
	HeapNode *temp = newhead;
	HeapNode *next = newhead->sibling;

	while(next != NULL) {

		if (temp->degree != next->degree || (next->sibling != NULL && temp->degree == next->sibling->degree)) {

			// Case 1: temp->degree != next->degree
         	// Case 2: temp->degree == next->degree == next->sibling->degree
			prev = temp;
			temp = next;

		} else {
			// Case 3: temp->degree == next->degree != next->sibling->degree && temp->key < next->key
			if (temp->key < next->key) {
				temp->sibling = next->sibling;
				next->parent = temp;
				next->sibling = temp->child;
				temp->child = next;
				temp->degree++;

			// Case 4: temp->degree == next->degree != next->sibling->degree && temp->key == next->key
			// if key is equal, use taskname as minor key
			} else if (temp->key == next->key) {

				if (temp->TaskName < next->TaskName) {
					temp->sibling = next->sibling;
					next->parent = temp;
					next->sibling = temp->child;
					temp->child = next;
					temp->degree++;

				} else if (temp->TaskName > next->TaskName) {
					if (prev == NULL) {
						newhead = next;
					}
					else {
						prev->sibling = next;
					}
					temp->parent = next;
					temp->sibling = next->child;
					next->child = temp;
					next->degree++;
					temp = next;
				}
			// Case 5: temp->degree == next->degree != next->sibling->degree && temp->key > next->key
			} else if (temp->key > next->key){
				if (prev == NULL) {
					newhead = next;
				}
				else {
					prev->sibling = next;
				}
				temp->parent = next;
				temp->sibling = next->child;
				next->child = temp;
				next->degree++;

				temp = next;
			}
		}
		next = temp->sibling;
	}
	return newhead;
}

// auxiliary function 3
// node1 is the node need to be removed，node2 is the previous node of node1
// Time complexity: O(log n)
void heapRemove(BinomialHeap *heap, HeapNode *node1, HeapNode *node2) {

	HeapNode *newhead = NULL;
	HeapNode *child = node1->child;
	
	if (node1 == heap->head)
		heap->head = node1->sibling;
	else {
		node2->sibling = node1->sibling;
	}

	while (child != NULL) {
		HeapNode *next;
		next = child->sibling;
		child->sibling = newhead;
		child->parent = NULL;
		newhead = child;
		child = next;
	}
	BinomialHeap *temp = newHeap();
	temp->head = newhead;
	heap->head = heapUnion(heap, temp);
	free(temp);
	heap->size--;
}

// Function 1
// k: key, n: task name, c: execution time, r: release time, d:deadline 
// You don't need to check if this task already exists in T
// put the time complexity analysis for Insert() here   
// Time complexity: O(log n)
void Insert(BinomialHeap *T, int k, int n, int c, int r, int d){

	HeapNode *newnode = newHeapNode(k, n, c, r, d);
	BinomialHeap *tempheap = newHeap();
	tempheap->head = newnode;
	tempheap->size++;
	if (T->head == NULL){
		T->head = newnode;
		T->size++;
	}
	else{
		T->head = heapUnion(T, tempheap);
		T->size++;
	}
}

// Function 2
// put your time complexity for RemoveMin() here
// Time complexity: O(log n)
HeapNode *RemoveMin(BinomialHeap *T){

	if(T->head == NULL) {
		return NULL;
	}

	HeapNode *min = T->head;
	HeapNode *min_prev = NULL;
	HeapNode *next = min->sibling;
	HeapNode *next_prev = min;
	HeapNode *newnode;

	while(next != NULL) {

		if(next->key < min->key) {
			min_prev = next_prev;
			min = next;
			
		}
		next_prev = next;
		next = next->sibling;
	}
	heapRemove(T, min, min_prev);
	return min;
}

// Function 3
// put your time complexity for Min() here
// Time complexity: O(log n)
int Min(BinomialHeap *T){

	assert(T != NULL);

	HeapNode *min = T->head;
	HeapNode *min_prev = NULL;
	HeapNode *next;
	HeapNode *next_prev = min;

	if (min->sibling == NULL) {
		return min->key;
	}
	else {
		next = min->sibling;
	}

	while(next != NULL) {

		if(next->key <= min->key) {

			min = next;
			min_prev = next_prev;
		}
		next_prev = next;
		next = next->sibling;
	}
	return min->key;
}

// put your time complexity analysis for MyTaskScheduler here
// Time complexity: O(log n) * 3 + O(n * log n) =  O(n log n) 
int TaskScheduler(char *f1, char *f2, int m ){

	float n;
	int count = 0;
	float array1[NUM] = {};
	float array2[NUM][4] = {};

	FILE *fp1;
	fp1 = fopen(f1, "r");
	if (fp1 == NULL) {
		printf("file1 does not exist.\n");
		exit(0);
	}
	while (fscanf(fp1, "%f", &n) != EOF){
			array1[count] = n;
			count++;
	}
	fclose(fp1);

	if (count == 0){
		printf("There is no content in this file.\n");
		exit(0);
	}
	if (count%4 != 0) {
		printf("input error.");
		exit(0);
	}

	for (int i = 0; i < count/4; i++){
		for (int j = 0; j < 4; j++){
			array2[i][j] = array1[4*i + j];
		}
	}

	for (int i = 0; i < count/4; i++) {
			if (array2[i][0] < 0 || array2[i][0] != (int)array2[i][0] ||
				array2[i][1] < 0 || array2[i][1] != (int)array2[i][1] || 
				array2[i][2] < 0 || array2[i][2] != (int)array2[i][2] ||
				array2[i][3] < 0 || array2[i][3] != (int)array2[i][3]) {

				printf("input error when reading the attribute of the task %d.", i+1);
				putchar('\n');
				exit(0);
			}	
	}

	HeapNode *newnode;
	BinomialHeap *Rheap = newHeap();
	BinomialHeap *Dheap = newHeap();
	BinomialHeap *tempheap = newHeap();

	for (int i = 0; i < count/4; i++){
		Insert(Rheap, array2[i][2], array2[i][0], array2[i][1], array2[i][2], array2[i][3]);
	}

	int realtime = 0;
	int core[NUM] = {0};
	HeapNode *tempnode;
	FILE *fp2 = fopen(f2, "w");

	/* 
	 * Rheap and Dhead are two priority queue which key is Release time and Deadline
	 * Time complexity: n * O(log n) =  O(n log n) 
	*/ 
	while (!(Rheap->size == 0 && Dheap->size == 0)){

		// when Rheap is not NULL
		// Time complexity: O(log n) for if 
		if (Rheap->size != 0) {
			while (realtime >= Min(Rheap)) {
				newnode = RemoveMin(Rheap);
				// 将Rheap中的release time符合要求的任务放到Dheap里
				Insert(Dheap, newnode->Dline, newnode->TaskName, newnode->Etime, newnode->Rtime, newnode->Dline);
				if(Rheap->size == 0) break;  // 没有这一句会导致Rheap remove最后一个元素后结束不了循环
			}
		}
		// Time complexity: log n for for loop
		for (int i = 0; i < m; i++) {
			if (core[i] == 0) {
				if (Dheap->size != 0){
					tempnode = RemoveMin(Dheap);

					if (realtime >= tempnode->key || (realtime + tempnode->Etime > tempnode->key)){
						fprintf(fp2, "%d core%d %d ", tempnode->TaskName, i+1, realtime);
						fprintf(fp2,"...");
						fprintf(fp2, "\n\nwhere task %d misses its deadline.", tempnode->TaskName);
						return 0;
					}
					core[i] = tempnode->Etime--;
					if (core[i] == 0) i--;
					fprintf(fp2, "%d core%d %d ", tempnode->TaskName, i+1, realtime);
				}
			}
			else if (core[i] != 0) {
				core[i]--;
				if (core[i] == 0) i--;
			}
		}
		realtime++;
	}
	fclose(fp2);
	return 1;
}

//sample main for testing 
int main() { 

	int i;
	i = TaskScheduler("samplefile1.txt", "feasibleschedule1.txt", 4);
	if (i == 0) printf("No feasible schedule!\n");
	/* There is a feasible schedule on 4 cores */

	i = TaskScheduler("samplefile1.txt", "feasibleschedule2.txt", 3);
	if (i == 0) printf("No feasible schedule!\n");
	/* There is no feasible schedule on 3 cores */

	i = TaskScheduler("samplefile2.txt", "feasibleschedule3.txt", 5);
	if (i == 0) printf("No feasible schedule!\n");
	/* There is a feasible schedule on 5 cores */

	i = TaskScheduler("samplefile2.txt", "feasibleschedule4.txt", 4);
	if (i == 0) printf("No feasible schedule!\n");
	/* There is no feasible schedule on 4 cores */

	i = TaskScheduler("samplefile3.txt", "feasibleschedule5.txt", 2);
	if (i == 0) printf("No feasible schedule!\n");
	/* There is no feasible schedule on 2 cores */

	i = TaskScheduler("samplefile4.txt", "feasibleschedule6.txt", 2);
	if (i == 0) printf("No feasible schedule!\n");
	/* There is a feasible schedule on 2 cores */ 

	return 0; 
}
