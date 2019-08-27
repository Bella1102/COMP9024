
// Integer Queue ADO implementation

#include "IntQueue.h"
#include <assert.h>

#define MAXITEMS 10

static struct {

	int item[MAXITEMS];
	int top;

} queueObject;

void QueueInit{

	queueObject.top = -1;
}

int QueueIsEmpty{

	return (queueObject.top < 0);
}

void QueueEnqueue(int n) { // insert int at end of queue 

	assert(queueObject.top < MAXITEMS-1); 
	queueObject.top++;

	int i;
   for (i = queueObject.top; i > 0; i--) {

		queueObject.item[i] = queueObject.item[i-1]; // move all elements up
	}s
	queueObject.item[0] = n; // add element at end of queue 

}

int QueueDequeue() { // remove int from front of queue 

	assert(queueObject.top > -1);

	int i = queueObject.top;
	int n = queueObject.item[i];

	queueObject.top--;
	return n; 
}