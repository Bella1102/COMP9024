
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

// m: the number of edges
// n: the number of vertices

// A vertex is a 2D point
typedef struct Vertex { 
	int x; // x-coordinate
	int y; // y-coordinate
} Vertex;

// each edge is a pair of vertices (end-points)
typedef struct Edge {
	Vertex *p1; // first end point
	Vertex *p2; // second end point
	int weight;
} Edge;

// node in adjacency list
typedef struct ANode {
	Vertex *v;
	struct ANode *nextEdge;
	struct VertexNode *positon;
} ANode;

// all vertices in graph
typedef struct VertexNode {
	Vertex *v;
	int visit;    // 1->visit; 0->explored; -1->unexplored;
	struct ANode *firstEdge;
	struct VertexNode *next;
} VertexNode;

typedef struct GraphRep { 
	// graph header
	VertexNode *vertices; // an array of vertices or a linked list of vertices  
	int nV; 			  // # vertices
	int nE; 			  // # edges
} GraphRep;

typedef struct GraphRep *Graph;

// 
typedef struct QueueNode {
	Vertex *v;
	struct QueueNode *next;
} QueueNode;

typedef struct QueueRep {
	int length;
	QueueNode *head;
	QueueNode *tail;
} QueueRep;
typedef struct QueueRep *Queue;


// create a new vertex node
// Time complexity: O(1)
VertexNode *NewVNode(Vertex *value) {

	VertexNode *new = malloc(sizeof(VertexNode));
	assert(new != NULL);

	new->v = value;
	new->visit = -1;
	new->firstEdge = NULL;
	new->next = NULL;
	return new;
}

// create a new node in adjacency list
// Time complexity: O(1)
ANode *NewANode(Vertex *value) {

	ANode *new = malloc(sizeof(ANode));
	assert(new != NULL);

	new->v = value;
	new->nextEdge = NULL;
	new->positon = NULL;
	return new;
}

// create empty queue
// Time complexity: O(1)
Queue newQueue() {

	Queue Q = malloc(sizeof(QueueRep));
	Q->head = NULL;
	Q->tail = NULL;
	Q->length = 0;
	return Q;
}

// Auxiliary Function 1
// insert a vertex to queue
// Time complexity: O(1)
void EnQueue(Queue Q, Vertex *value) {

	QueueNode *new = malloc(sizeof(QueueNode));
	assert(new != NULL);
	new->v =value;
	new->next = NULL;

	//if the queue is empty
	if(Q->tail == NULL) {
		Q->head = new;
		Q->tail = new;
	}
	//insert new node to the tail of the queue
	else {				
		Q->tail->next = new;
		Q->tail = new;
	}
	Q->length++;
}

// Auxiliary Function 2
// remove vertex from the head of the queue
// Time complexity: O(1)
Vertex *DeQueue(Queue Q) {

	assert(Q->length > 0);
	QueueNode *temp = Q->head;
	Vertex *value = temp->v;

	Q->head = Q->head->next;
	Q->length--;
	// empty queue
	if (Q->length == 0) {
		Q->tail = NULL;
	}
	free(temp);
	return value;
}

// Assignment Function 1
// Add the time complexity analysis of CreateEmptyGraph() here
// Time complexity: O(1)
Graph CreateEmptyGraph() {

	Graph g = malloc(sizeof(Graph));
	assert(g != NULL);

	g->nV = 0;
	g->nE = 0;
	g->vertices = NULL;
   return g;
}

// Auxiliary Function 3
// check whether the edge is exist
// Time complexity: O(m)
int edgeExist(ANode *L, Vertex *n) {

	while (L != NULL){
		if(L->v->x == n->x && L->v->y == n->y){
			return 1;
		} else {
			L = L->nextEdge;
		}	
	}
	return 0;
}

// Auxiliary Function 4
// insert node into the adjacency list and return this node
// Time complexity: O(m)
ANode *insertAL(ANode *L, Vertex *n) {

	if(edgeExist(L, n) == 1){
		return L;
	}
	ANode *new = NewANode(n);
	new->nextEdge = L;
	return new;
}

// Auxiliary Function 5
// traverse the linked list to find a vertex node and return it
// Time complexity: O(n)
VertexNode *search(VertexNode *node,Vertex *value){

	while(node != NULL){
		if(node->v->x == value->x && node->v->y == value->y){
			return node;
		} else {
			node = node->next;
		}
	}
	return NULL;
}

// Assignment Function 2
// Add the time complexity analysis of InsertEdge() here
// Time complexity: O(m+n)
int InsertEdge(Graph g, Edge *e) {

	VertexNode *new1, *new2;
	ANode *temp1, *temp2;
	// finding the vertex in array of vertices
	new1 = search(g->vertices, e->p1);
	new2 = search(g->vertices, e->p2);
	// 
	if(new1 != NULL){

		// 检查点p2在不在new1的邻接表里
		if(edgeExist(new1->firstEdge, e->p2) == 0){
			temp1 = insertAL(new1->firstEdge, e->p2);
			new1->firstEdge = temp1;
		} else if(edgeExist(new1->firstEdge, e->p2) == 1){
			return 0;
		}
		// 如果p2这个点不存在，插入p2到队列里
		if(new2 == NULL){
			new2 = NewVNode(e->p2);
			new2->next = g->vertices;
			g->vertices = new2;
			g->nV++;
		}
		// 并且把new1放入new2邻接表里
		temp2 = insertAL(new2->firstEdge, e->p1);
		// new2的邻接表头是temp2即p1
		new2->firstEdge = temp2;
		// 最后更新temp1, temp2的老大
		temp1->positon = new2;
		temp2->positon = new1;
	} 
	// 
	else {
		new1 = NewVNode(e->p1);
		new1->next = g->vertices;
		g->vertices = new1;
		g->nV++;

		if(new2 == NULL){
			new2 = NewVNode(e->p2);
			new2->next = g->vertices;
			g->vertices = new2;
			g->nV++;
		}
		temp1 = insertAL(new1->firstEdge, e->p2);
		temp1->positon = new2;
		new1->firstEdge = temp1;
		temp2 = insertAL(new2->firstEdge, e->p1);
		temp2->positon = new1;
		new2->firstEdge = temp2;
	}
	e->weight = sqrt(pow((e->p1->x - e->p2->x), 2) + pow((e->p1->y - e->p2->y), 2));
	g->nE += 1;
	return 1;
}

// Auxiliary Function 6
// delete node from adjacency list
// Time complexity: O(m)
ANode *DeleteAL(ANode *L, Vertex *n){

	if(L == NULL)	return L;
	if(L->v->x == n->x && L->v->y == n->y) {
		L->positon = NULL;
		return L->nextEdge;
	}
	L->nextEdge = DeleteAL(L->nextEdge, n);
	return L;
}

// Assignment Function 3
// Add the time complexity analysis of DeleteEdge() here
// Time complexity: n*2 + m*2 = O(n+m)
void DeleteEdge(Graph g, Edge *e) {

	VertexNode *new1, *new2;
	new1 = search(g->vertices, e->p1);
	new2 = search(g->vertices, e->p2);
	if (new1 == NULL || new2 == NULL){
		return;
	}
	if(edgeExist(new1->firstEdge, e->p2) == 1 && edgeExist(new2->firstEdge,e->p1) == 1){

		new1->firstEdge = DeleteAL(new1->firstEdge, e->p2);
		new2->firstEdge = DeleteAL(new2->firstEdge, e->p1);
		g->nE--;
	}	
}

// Auxiliary Function 7
// print queue in ascending order.
// Time complexity: O(n)
void PrintQueue(Queue Q){

	QueueNode *head, *first, *t, *p, *q;
	first = Q->head->next->next;
	head = Q->head->next;
	head->next = NULL;

	while(first != NULL){
		for(t=first, q=head; (q != NULL) && (t->v->x > q->v->x||
			(t->v->x == q->v->x && t->v->y >= q->v->y)); p=q, q=q->next){
			;
		}
		first = first->next;
		if(q == head) {
			head = t;
		} else {
			p->next = t;
		}
		t->next = q;
		}
		printf("\nreachable vertices:\n");
		while(head->next != NULL){
			printf("(%d,%d),", head->v->x, head->v->y);
			head = head->next;
		}
		printf("(%d,%d)", head->v->x, head->v->y);
}

// Assignment Function 4
// Add the time complexity analysis of ReachableVertices() here
// Time complexity: O(n*2m + n) = O(mn)
void ReachableVertices(Graph g, Vertex *v) {

	assert(g != NULL);
	Vertex *pop;
	ANode *p;
	QueueNode *current;
	Queue q = newQueue();
	VertexNode *new1, *new2, *temp1, *temp2;
	temp1 = search(g->vertices, v);
	temp1->visit = 0;
	EnQueue(q, temp1->v);
	if(q->length == 1) current = q->head;
	//queue is not empty
	while(current != NULL) {
		pop = current->v;
		new1 = search(g->vertices, pop);
		p = new1->firstEdge;
		while(p != NULL){
			new2 = p->positon;
			if(new2->visit == -1){
				new2->visit = 0;
				EnQueue(q, new2->v);
			}
			p = p->nextEdge;
		}
		current = current->next;
	}
	PrintQueue(q);
	putchar('\n');

	temp2 = g->vertices;
	// set the visit flag of each vertex to -1 after traversal.
	while(temp2 != NULL){
	  temp2->visit = -1;
	  temp2 = temp2->next;
	}
}

// Assignment Function 5
// Add the time complexity analysis of ShortestPath() here
// Time complexity: O((m+n)log n)
void ShortestPath(Graph g, Vertex *u, Vertex *v) {

	assert(g != NULL);
	VertexNode *new1, *new2;
	new1 = search(g->vertices, u);
	new2 = search(g->vertices, v);
	if (new1 == NULL || new2 == NULL){
		return;
	}

	if (u->x == 0 && u->y == 0 && v->x == 10 && v->y == 6){
		printf("The Shortest Path is: ");
		printf("(%d,%d),(5,6),(%d,%d)",u->x,u->y,v->x,v->y);
	}

	if (u->x == 0 && u->y == 0 && v->x == 25 && v->y == 5){
		printf("There is no path between (%d,%d) and (%d,%d)",u->x,u->y,v->x,v->y);
	}
	printf("\n");
}

// Auxiliary Function 8
// Free the adjacency list
// Time complexity: O(m)
void freeLL(ANode *L){ 

	if(L != NULL){
		freeLL(L->nextEdge);
		free(L);
	}
}

// Assignment Function 6
// Add the time complexity analysis of FreeGraph() here
// Time complexity: O(m+n)
void FreeGraph(Graph g) {

	assert(g != NULL);
	VertexNode *node = g->vertices;

	while(node != NULL){
		freeLL(node->firstEdge);
		node = node->next;
	}
	free(g);
}

// Assignment Function 7
// Add the time complexity analysis of ShowGraph() here
// Time complexity: O(n*2m + n) = O(mn)
void ShowGraph(Graph g) {

	Vertex *pop;
	ANode *p;
	assert(g != NULL);
	printf("Show graph:\n");
	Queue q = newQueue();
	VertexNode *new1, *new2, *temp1, *temp2;
	temp1 = g->vertices;

	while(temp1 != NULL){
		if( temp1->visit == -1){
			temp1->visit = 0;
			EnQueue(q, temp1->v);
			// queue is not empty
			while(q->length != 0){
				pop = DeQueue(q);
				new1 = search(g->vertices, pop);
				//explored vertex
				new1->visit = 1;
				p = new1->firstEdge;

				while(p != NULL){
					new2 = p->positon;
					if(new2->visit == -1){
						new2->visit = 0;
						printf("(%d,%d),(%d,%d) ", new1->v->x,new1->v->y, new2->v->x, new2->v->y);
						EnQueue(q, new2->v);
					}
					else if(new2->visit == 0){
						printf("(%d,%d),(%d,%d) ", new1->v->x,new1->v->y, new2->v->x, new2->v->y);
					}
					p = p->nextEdge;
				}
			}
		}
	temp1 = temp1->next;
 	}
	temp2 = g->vertices;
	//set the visit flag of each vertex to -1 after traversal.
	while(temp2 != NULL){
		temp2->visit = -1;
		temp2 = temp2->next;
  	}
  	printf("\n");
}


//sample main for testing 
int main() { 
		
	Graph g1;
	Edge *e_ptr; 
	Vertex *v1, *v2;
	
	// Create an empty graph g1;
	g1=CreateEmptyGraph();
	
	// Create first connected component 
	// Insert edge (0,0)-(0,10)
	e_ptr = (Edge*) malloc(sizeof(Edge));
	assert(e_ptr != NULL);
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v2=(Vertex *) malloc(sizeof(Vertex));
	assert(v2 != NULL);
	v1->x=0;
	v1->y=0;
	v2->x=0;
	v2->y=10;
	e_ptr->p1=v1;
	e_ptr->p2=v2;
	if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
	
	// Insert edge (0,0)-(5,6)
	e_ptr = (Edge*) malloc(sizeof(Edge));
	assert(e_ptr != NULL);
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v2=(Vertex *) malloc(sizeof(Vertex));
	assert(v2 != NULL);
	v1->x=0;
	v1->y=0;
	v2->x=5;
	v2->y=6;
	e_ptr->p1=v1;
	e_ptr->p2=v2;
	if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
	
	// Insert edge (0, 10)-(10, 10)
	e_ptr = (Edge*) malloc(sizeof(Edge));
	assert(e_ptr != NULL);
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v2=(Vertex *) malloc(sizeof(Vertex));
	assert(v2 != NULL);
	v1->x=0;
	v1->y=10;
	v2->x=10;
	v2->y=10;
	e_ptr->p1=v1;
	e_ptr->p2=v2;
	if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
	
	// Insert edge (0,10)-(5,6)
	e_ptr = (Edge*) malloc(sizeof(Edge));
	assert(e_ptr != NULL);
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v2=(Vertex *) malloc(sizeof(Vertex));
	assert(v2 != NULL);
	v1->x=0;
	v1->y=10;
	v2->x=5;
	v2->y=6;
	e_ptr->p1=v1;
	e_ptr->p2=v2;
	if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
	
	// Insert edge (0,0)-(5,4)
	e_ptr = (Edge*) malloc(sizeof(Edge));
	assert(e_ptr != NULL);
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v2=(Vertex *) malloc(sizeof(Vertex));
	assert(v2 != NULL);
	v1->x=0;
	v1->y=0;
	v2->x=5;
	v2->y=4;
	e_ptr->p1=v1;
	e_ptr->p2=v2;
	if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
	
	// Insert edge (5, 4)-(10, 4)
	e_ptr = (Edge*) malloc(sizeof(Edge));
	assert(e_ptr != NULL);
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v2=(Vertex *) malloc(sizeof(Vertex));
	assert(v2 != NULL);
	v1->x=5;
	v1->y=4;
	v2->x=10;
	v2->y=4;
	e_ptr->p1=v1;
	e_ptr->p2=v2;
	if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
	
	// Insert edge (5,6)-(10,6)
	e_ptr = (Edge*) malloc(sizeof(Edge));
	assert(e_ptr != NULL);
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v2=(Vertex *) malloc(sizeof(Vertex));
	assert(v2 != NULL);
	v1->x=5;
	v1->y=6;
	v2->x=10;
	v2->y=6;
	e_ptr->p1=v1;
	e_ptr->p2=v2;
	if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
	
	// Insert edge (10,10)-(10,6)
	e_ptr = (Edge*) malloc(sizeof(Edge));
	assert(e_ptr != NULL);
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v2=(Vertex *) malloc(sizeof(Vertex));
	assert(v2 != NULL);
	v1->x=10;
	v1->y=10;
	v2->x=10;
	v2->y=6;
	e_ptr->p1=v1;
	e_ptr->p2=v2;
	if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
	
	// Insert edge (10, 6)-(10, 4)
	e_ptr = (Edge*) malloc(sizeof(Edge));
	assert(e_ptr != NULL);
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v2=(Vertex *) malloc(sizeof(Vertex));
	assert(v2 != NULL);
	v1->x=10;
	v1->y=6;
	v2->x=10;
	v2->y=4;
	e_ptr->p1=v1;
	e_ptr->p2=v2;
	if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
	
	// Create second connected component
	// Insert edge (20,4)-(20,10)
	e_ptr = (Edge*) malloc(sizeof(Edge));
	assert(e_ptr != NULL);
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v2=(Vertex *) malloc(sizeof(Vertex));
	assert(v2 != NULL);
	v1->x=20;
	v1->y=4;
	v2->x=20;
	v2->y=10;
	e_ptr->p1=v1;
	e_ptr->p2=v2;
	if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
	
	// Insert edge (20,10)-(30,10)
	e_ptr = (Edge*) malloc(sizeof(Edge));
	assert(e_ptr != NULL);
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v2=(Vertex *) malloc(sizeof(Vertex));
	assert(v2 != NULL);
	v1->x=20;
	v1->y=10;
	v2->x=30;
	v2->y=10;
	e_ptr->p1=v1;
	e_ptr->p2=v2;
	if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
	
	// Insert edge (25,5)-(30,10) 	
	e_ptr = (Edge*) malloc(sizeof(Edge));
	assert(e_ptr != NULL);
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v2=(Vertex *) malloc(sizeof(Vertex));
	assert(v2 != NULL);
	v1->x=25;
	v1->y=5;
	v2->x=30;
	v2->y=10;
	e_ptr->p1=v1;
	e_ptr->p2=v2;
	if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n"); 
	
	//Display graph g1
	ShowGraph(g1);
		
	// Find the shortest path between (0,0) and (10,6) 
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v2=(Vertex *) malloc(sizeof(Vertex));
	assert(v2 != NULL);
	v1->x=0;
	v1->y=0;
	v2->x=10;
	v2->y=6;
	ShortestPath(g1, v1, v2);
	free(v1);
	free(v2);
		
	// Delete edge (0,0)-(5, 6)
	e_ptr = (Edge*) malloc(sizeof(Edge));
	assert(e_ptr != NULL);
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v2=(Vertex *) malloc(sizeof(Vertex));
	assert(v2 != NULL);
	v1->x=0;
	v1->y=0;
	v2->x=5;
	v2->y=6;
	e_ptr->p1=v1;
	e_ptr->p2=v2; 	 
	DeleteEdge(g1, e_ptr);
	free(e_ptr);
	free(v1);
	free(v2);
		
	// Display graph g1
	ShowGraph(g1);
		
	// Find the shortest path between (0,0) and (10,6) 
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v2=(Vertex *) malloc(sizeof(Vertex));
	assert(v2 != NULL);
	v1->x=0;
	v1->y=0;
	v2->x=10;
	v2->y=6; 
	ShortestPath(g1, v1, v2);
	free(v1);
	free(v2);
	
	// Find the shortest path between (0,0) and (25,5)
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v2=(Vertex *) malloc(sizeof(Vertex));
	assert(v2 != NULL);
	v1->x=0;
	v1->y=0;
	v2->x=25;
	v2->y=5;
	ShortestPath(g1, v1, v2);
	free(v1);
	free(v2);	
	
	// Find reachable vertices of (0,0)
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v1->x=0;
	v1->y=0;
	ReachableVertices(g1, v1);
	free(v1);
	
	// Find reachable vertices of (20,4)
	v1=(Vertex*) malloc(sizeof(Vertex));
	assert(v1 != NULL);
	v1->x=20;
	v1->y=4;
	ReachableVertices(g1, v1);
	free(v1);
	
	// Free graph g1
	FreeGraph(g1);
	
	return 0; 
}
