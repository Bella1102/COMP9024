
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NUM 20480

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like 

// 1. data type for avl tree nodes
typedef struct AVLTreeNode {
	
	int key;       //key of this item
	int value;     //value (int) of this item 
	int height;    //height of the subtree rooted at this node
	struct AVLTreeNode *parent;   //pointer to parent
	struct AVLTreeNode *left;     //pointer to left child
	struct AVLTreeNode *right;    //pointer to right child

} AVLTreeNode;

// 2. data type for AVL trees
typedef struct AVLTree {
	
	int  size;           // count of items in avl tree
	AVLTreeNode *root;   // root

} AVLTree;

// 3. create a new AVLTreeNode
AVLTreeNode *newAVLTreeNode(int k, int v) {
		
	AVLTreeNode *new;
	new = malloc(sizeof(AVLTreeNode));
	assert(new != NULL);

	new->key = k;
	new->value = v;
	new->height = 0;      // height of this new node is set to 0
	new->left = NULL;     // this node has no child
	new->right = NULL;
	new->parent = NULL;   // no parent
	return new;
}

// 4. create a new empty AVL tree
AVLTree *newAVLTree() {
	
	AVLTree *T;
	T = malloc(sizeof (AVLTree));
	assert (T != NULL);

	T->size = 0;
	T->root = NULL;
	return T;
}

// auxiliary struct 1
typedef struct array {
	
	int arr[NUM][2];
	int row;
	
} array;

// All auxiliary functions collection
int max(int a, int b);
int height(AVLTreeNode *N);
AVLTreeNode *leftRotate(AVLTreeNode *x);
AVLTreeNode *rightRotate(AVLTreeNode *y);
int getBalance(AVLTreeNode *node);
AVLTreeNode *InsertNodeToNode(AVLTreeNode *node, int key, int value);
AVLTreeNode *minValueNode(AVLTreeNode *node);
AVLTreeNode *deleteNodeFromNode(AVLTreeNode *root, int key, int value);
AVLTree *GetTree(char *buff);
void inOrder(AVLTreeNode *root);
array inOrderGet(AVLTreeNode *root);
AVLTreeNode *SearchNode(AVLTreeNode *node, int k, int v);
void FreeNode(AVLTreeNode *node);

// auxiliary function 1
// get maximum of two integers 
// time complexity: O(1)
int max(int a, int b) { 
	
	return (a >= b) ? a : b; 
}

// auxiliary function 2
// get the height of the subtree rooted with N
// time complexity: O(1)
int height(AVLTreeNode *N) { 
	
	if (N == NULL) 
		return 0; 
	return N->height; 
}

// auxiliary function 3
// left rotate subtree which rooted with x 
// time complexity: O(1)
AVLTreeNode *leftRotate(AVLTreeNode *x) { 
	
	AVLTreeNode *y = x->right; 
	AVLTreeNode *T2 = y->left; 
	AVLTreeNode *temp = x->parent; 
	
	y->left = x;
	x->right = T2;
	x->parent = y; 
	y->parent = temp;
	//T2->parent = x; //??????

	if (temp != NULL) {
		if (temp->left == x) {
			temp->left = y;
		} else {
			temp->right = y;
		}
	}

	x->height = max(height(x->left), height(x->right))+1; 
	y->height = max(height(y->left), height(y->right))+1; 
	return y; 
}

// auxiliary function 4
// right rotate subtree which rooted with y 
// time complexity: O(1)
AVLTreeNode *rightRotate(AVLTreeNode *y) { 
	
	AVLTreeNode *x = y->left; 
	AVLTreeNode *T2 = x->right; 
	AVLTreeNode *temp = y->parent; 
	
	x->right = y;
	y->left = T2;
	y->parent = x;
	x->parent = temp;
	T2->parent = y;

	if (temp != NULL) {
		if (temp->left == y) {
			temp->left = x;
		} else {
			temp->right = x;
		}
	}
	
	y->height = max(height(y->left), height(y->right))+1; 
	x->height = max(height(x->left), height(x->right))+1; 
	return x; 
}

// auxiliary function 5
// judge whether the node N is balance or not 
// time complexity: O(1)
int getBalance(AVLTreeNode *node) { 
	
	if (node == NULL) 
		return 0;
		
	return height(node->left) - height(node->right);
}

// auxiliary function 6
// Recursive function to insert a node to a tree with given root. 
// It returns root of the modified subtree. 
// time complexity: O(log n)
AVLTreeNode *InsertNodeToNode(AVLTreeNode *node, int key, int value) {

	int balance;
	AVLTreeNode *newnode = newAVLTreeNode(key, value);

	if (node == NULL) {
		return(newnode); 
	}
	
	if (key < node->key) {

		node->left  = InsertNodeToNode(node->left, key, value); 
		node->height = max(height(node->left), height(node->right))+1;
		balance = getBalance(node); 
		if (balance > 1) {

			if (key < node->left->key || (key == node->left->key && value < node->left->value)) {
				return rightRotate(node);

			} else if (key > node->left->key || (key == node->left->key && value > node->left->value)) {

				node->left = leftRotate(node->left); 
				return rightRotate(node);
			} 
		} else {
			node->left->parent = node;
		}
	}
	if (key > node->key) {
		node->right = InsertNodeToNode(node->right, key, value); 
		node->height = max(height(node->left), height(node->right))+1;
		balance = getBalance(node); 
		if (balance < -1) {

			if (key > node->right->key || (key == node->right->key && value > node->right->value)) {
				return leftRotate(node);

			} else if (key < node->right->key || (key == node->right->key && value < node->right->value)) {
					node->right = rightRotate(node->right); 
					return leftRotate(node); 
			}
		} else {
			node->right->parent = node;
		}
	}
	if (key == node->key){ 

		if (value == node->value) {
			return node;
				
		} else if (value < node->value) {
			node->left  = InsertNodeToNode(node->left, key, value);
			node->height = max(height(node->left), height(node->right))+1;
			balance = getBalance(node); 
			if (balance > 1) {

				if (key < node->left->key || (key == node->left->key && value < node->left->value)) {
					return rightRotate(node);

				} else if (key > node->left->key || (key == node->left->key && value > node->left->value)) {

					node->left = leftRotate(node->left); 
					return rightRotate(node);
				}
			} else {
				node->left->parent = node;
			}	
		} else if (value > node->value) {

			node->right = InsertNodeToNode(node->right, key, value); 
			node->height = max(height(node->left), height(node->right))+1;
			balance = getBalance(node); 
			if (balance < -1) {

				if (key > node->right->key || (key == node->right->key && value > node->right->value)) {
					return leftRotate(node);

				} else if (key < node->right->key || (key == node->right->key && value < node->right->value)) {
						node->right = rightRotate(node->right); 
						return leftRotate(node); 
				}
			} else {
				node->right->parent = node;
			}
		}
	}
	return node;
}

// auxiliary function 7
// return the node with minimum key value found in BST tree. 
// time complexity: O(log n)
AVLTreeNode *minValueNode(AVLTreeNode *node) { 
	
	AVLTreeNode *current = node; 

	while (current->left != NULL) {	
		current = current->left;
	}
	return current;
}

// auxiliary function 8
// Recursive function to delete a node with given key from subtree with given root. 
// It returns root of the modified subtree. 
// time complexity: O(log n)
AVLTreeNode *deleteNodeFromNode(AVLTreeNode *root, int key, int value) { 
	
	AVLTreeNode *nnode = newAVLTreeNode(key, value);
	
	// 1. Perform standard BST delete 
	if (root == NULL) 
		return root;
			
	if (key < root->key) {
		root->left = deleteNodeFromNode(root->left, key, value); 
		
	} else if (key > root->key) {	
		root->right = deleteNodeFromNode(root->right, key, value); 
		
	} else if (key == root->key){
		
		if (value < root->value) {
			root->left = deleteNodeFromNode(root->left, key, value); 
					
		} else if (value > root->value) {
			root->right = deleteNodeFromNode(root->right, key, value); 
			
		} else if (value == root->value) {
			
            // if (key,value) is same as root’s (key, value), this is the node to be deleted
			// node with only one child or no child 
			if( (root->left == NULL) || (root->right == NULL) ) { 
				
				AVLTreeNode *temp = root->left ? root->left : root->right; 
		
				// No child case 
				if (temp == NULL) { 
					
					temp = root; 
					root = NULL; 
				} 
				// One child case, Copy the contents of the non-empty child
				else {
					*root = *temp;
					root->left = temp->left;
					root->right = temp->right;
					temp->parent = root->parent;
				}            
				free(temp); 

			} else {
				// node with two children: Get the inorder immediate successor 
				AVLTreeNode *temp = minValueNode(root->right); 
		
				// Copy the inorder successor's data to this node 
				root->key = temp->key; 
				root->value = temp->value;
		
				// Delete the inorder successor 
				root->right = deleteNodeFromNode(root->right, temp->key, temp->value); 
			} 
		}
	} 
	// If the tree had only one node then return 
	if (root == NULL) 
		return root; 	
	// else: update the height of this tree
	root->height = 1 + max(height(root->left), height(root->right)); 
	
	int balance = getBalance(root); 
	// 4.1 Left Left Case  
	if (balance > 1 && getBalance(root->left) >= 0) {
		return rightRotate(root);
	}
	// 4.2 Right Right Case  
	if (balance < -1 && getBalance(root->right) <= 0) {
		return leftRotate(root); 
	}
	// 4.3 Left Right Case 
	if (balance > 1 && getBalance(root->left) < 0) { 
		root->left =  leftRotate(root->left); 
		return rightRotate(root); 
	}
	// 4.4 Right Left Case  
	if (balance < -1 && getBalance(root->right) > 0) { 
		root->right = rightRotate(root->right); 
		return leftRotate(root); 
	} 

	return root; 
} 

// auxiliary function 1-0
// get (key, value) from string and make a newtree
// time complexity: O(n logn)
AVLTree *GetTree(char *buff) {

	AVLTree *newtree = newAVLTree();
	AVLTreeNode *newnode;

	char *start, *end;
	char item[NUM][20];
	int  count = 0, row = 0;
	int  key, value; 
	
	start = buff;
	while(1){
		start = strchr(start, '(');	// return pointer which point to "("
		if(start == NULL ) break;
		end = strchr(start, ')');	// return pointer which point to ")"
		if(end == NULL ) break;
			
		if(++start < end) {
			
			memcpy(item[count++], start, end - start);      // copy (end - start) chars from start to item[]
			sscanf(item[count-1], "%d, %d", &key, &value);  // scan numbers into array

			if (row == 0) {
				newnode = newAVLTreeNode(key, value);
			} else {
				newnode = InsertNodeToNode(newnode, key, value);
			}	
			row++;
		}
	}
	newtree->size = row;
	newtree->root = newnode;

	return newtree;
}

// 1. put your time complexity analysis of CreateAVLTree() here
// requirement: cannot be higher than O(n logn).
// time complexity mainly depend on Gettree function
// time complexity: O(n logn)
AVLTree *CreateAVLTree(const char *filename){
	
	AVLTree *newtree = newAVLTree();
	AVLTreeNode *newnode;
	
	if (strcmp(filename, "stdin") == 0){
		
		char *buff, *ch;

		buff = malloc(NUM);  
		ch = malloc(1000);
		assert(buff != NULL);
		assert(ch != NULL);
		
	    while(strcmp(ch, "\n")){
		
			fgets(ch, NUM, stdin);
			strcat(buff, ch);
		}

		newtree = GetTree(buff);
		free(buff);
		free(ch);

		return newtree;
		
	} else {
		FILE *fp;
		char *buff;
		int  FileSize;
		
		fp = fopen(filename, "r");
		if (fp == NULL){
			printf("Can't open file or file doesn't exist.\n");
			exit(0);
		}
		
		fseek(fp, 0, SEEK_END);  // fp point to the end of the file
		FileSize = ftell(fp);    // return the current location of fp(total number of char in file)
		fseek(fp, 0, SEEK_SET);  // fp point to the start of the file
		
		buff = malloc(FileSize + 1);  
		assert(buff != NULL);
		fread(buff, FileSize, 1, fp); // read from fp to buff (1 FileSize data)
		fclose(fp);
		
		newtree = GetTree(buff);
		free(buff);	
		
		return newtree;
	}	
}

// auxiliary function 2-0
// In-order traversal to get all (key, value)
// time complexity: O(n)
int globalcount = 0;
array abc;
array inOrderGet(AVLTreeNode *root) {
	
	if (root != NULL) {

		inOrderGet(root->left);
		abc.arr[globalcount][0] = root->key;
		abc.arr[globalcount][1] = root->value;
		globalcount++;
		inOrderGet(root->right);
	}
	abc.row = globalcount;
	return abc;
}
// auxiliary function 2-1
// time complexity: O(n)
AVLTreeNode *CloneAVLNode(AVLTreeNode *root){

	if (root == NULL){
		return NULL;
	}
	AVLTreeNode *newroot = newAVLTreeNode(root->key, root->value);
	newroot->height = root->height;
	newroot->left = CloneAVLNode(root->left);
	newroot->right = CloneAVLNode(root->right);
	return newroot;
}

// 2. put your time complexity for CloneAVLTree() here
// requirement: cannot be higher than O(n).
// time complexity: O(n)
AVLTree *CloneAVLTree(AVLTree *T){

	assert(T != NULL);
	AVLTreeNode *temp;
	AVLTree *newtree = newAVLTree();
	temp = CloneAVLNode(T->root);

	newtree->root = temp;
	newtree->size = T->size;
	return newtree;
}
// auxiliary function 3-0
// time complexity: O(n)
int AVLTreeSize(AVLTreeNode *root){

    if (root != NULL) 
		return 0;
    return AVLTreeSize(root->left) + AVLTreeSize(root->right) + 1;
}

// 3. put your time complexity for ALVTreesUNion() here
// requirement: cannot be higher than O((m+n)log(m+n)),.
// time complexity: m + n + n + nlogn = O(m + nlogn)
AVLTree *AVLTreesUnion(AVLTree *T1, AVLTree *T2){

    AVLTree *newtree = CloneAVLTree(T1);
	AVLTreeNode *newnode;
	array arr1;
    int count;

	globalcount = 0;
    arr1 = inOrderGet(T2->root);

	for (int i = 0; i < arr1.row; i++){

        newnode = InsertNodeToNode(newtree->root, arr1.arr[i][0], arr1.arr[i][1]);
	}
	count = AVLTreeSize(newnode);
    newtree -> root = newnode;
    newtree -> size = count;

    return newtree;
}

// 4. put your time complexity for ALVTreesIntersection() here
// requirement: cannot be higher than O(m+n+k log k).
// time complexity:  O(m+n+klog k)
AVLTree *AVLTreesIntersection(AVLTree *T1, AVLTree *T2){

    AVLTree *newtree = newAVLTree();
	AVLTreeNode *newnode;
	array arr1, arr2, arr3;
	int num1, num2;
	int i = 0, j = 0, count = 0;
	
	globalcount = 0;
	arr1 = inOrderGet(T1->root);
	globalcount = 0;
    arr2 = inOrderGet(T2->root);
	num1 = arr1.row;
	num2 = arr2.row;

	// find the intersection of arr1 & arr2
	while (i < num1 && j < num2) {

		if (arr1.arr[i][0] == arr2.arr[j][0]) {

			if (arr1.arr[i][1] == arr2.arr[j][1]) {

				arr3.arr[count][0] = arr1.arr[i][0];
				arr3.arr[count][1] = arr1.arr[i][1];
				i++;
				j++;
				count++;

			} else if (arr1.arr[i][1] < arr2.arr[j][1]) {
				i++;

			} else if (arr1.arr[i][1] > arr2.arr[j][1]) {
				j++;
			}
		} else if (arr1.arr[i][0] < arr2.arr[j][0]) {
			i++;
		}
		else if (arr1.arr[i][0] > arr2.arr[j][0]) {
			j++;
		}
	}
	arr3.row = count;

	for(int m = 0; m < count; m++) {
	
		if (m == 0){
			newnode = newAVLTreeNode(arr3.arr[0][0], arr3.arr[0][1]);
		} else {
			newnode = InsertNodeToNode(newnode, arr3.arr[m][0], arr3.arr[m][1]);
		}		
	}
	newtree->size = count;
	newtree->root = newnode;
	return newtree;	
}

// 5. put the time complexity analysis for InsertNode() here
// requirement: cannot be higher than O(log n).
// time complexity: log n + log n = O(log n)
int InsertNode(AVLTree *T, int k, int v){

    AVLTreeNode *newnode;
    newnode = SearchNode(T->root, k, v); //If the item is found, returns this node; else return NULL

    if (newnode == NULL) {

        newnode = InsertNodeToNode(T->root, k, v);
		T->root = newnode;
        T->size = T->size + 1;
        return 1;

    } else {
        return 0;
    }
}

// 6. put your time complexity for DeleteNode() here
// requirement: cannot be higher than O(log n).
// time complexity: log n + log n = O(log n)
int DeleteNode(AVLTree *T, int k, int v){

    AVLTreeNode *newnode;
    newnode = SearchNode(T->root, k, v); //If the item is found, returns this node; else return NULL

    if (newnode != NULL) {

        newnode = deleteNodeFromNode(T->root, k, v);
		T -> root = newnode;
        T->size = T->size - 1;
        return 1;

    } else {
        return 0;
    }
}

// auxiliary function 7-0
// time complexity: O(log n)
AVLTreeNode *SearchNode(AVLTreeNode *node, int k, int v) {

	if (node == NULL) {

		return node;
    }
	if (k == node->key) {

		if (v == node->value) {
			return node;

		} else if (v < node->value) {
			return SearchNode(node->left, k, v);

		} else if (v > node->value) {
			return SearchNode(node->right, k, v);
		}
	} else if (k < node->key) {
		return SearchNode(node->left, k, v);

	} else if (k > node->key) {
		return SearchNode(node->right, k, v);
	} 
	return NULL;
}

// 7. put your time complexity analysis for Search() here
// requirement: cannot be higher than O(log n).
// time complexity: O(log n)
AVLTreeNode *Search(AVLTree *T, int k, int v){

    AVLTreeNode *newnode;
    newnode = SearchNode(T->root, k, v);
    return newnode;
}

// auxiliary function 8-0
// time complexity: O(n)
void FreeNode(AVLTreeNode *node) {
	
	if (node == NULL){
		return;
		
	} else if (node->left != NULL) {
		FreeNode(node->left);
		
	} else if (node->right != NULL) {	
		FreeNode(node->right);
	}
	free(node);
}

// 8. put your time complexity analysis for freeAVLTree() here
// requirement: cannot be higher than O(n).
// time complexity: O(n)
void FreeAVLTree(AVLTree *T) {
	
	FreeNode(T->root);
	free(T);
}

// auxiliary function 9-0
// In-order traversal
// time complexity: O(n)
void inOrder(AVLTreeNode *root) {
		
	if (root != NULL) {

		inOrder(root->left);
		printf("(%d, %d), %d\n", root->key, root->value, root->height);
		inOrder(root->right);
	}
}

// 9. put your time complexity analysis for PrintAVLTree() here
// requirement: cannot be higher than O(n).
// time complexity: O(n)
void PrintAVLTree(AVLTree *T){
	
	assert(T != NULL);
	inOrder(T->root);
	putchar('\n');	
}


void oo(AVLTreeNode *root) {
		
	if (root != NULL) {

		oo(root->left);
		oo(root->right);
		if (root->left == NULL && root->right == NULL){
			root->height = 0;
		}
		else{
			root->height = 1 + max(height(root->left), height(root->right)); 
		}

	}
}

//sample main for testing 
int main() { 

	int i,j;
	AVLTree *tree1, *tree2, *tree3, *tree4, *tree5, *tree6, *tree7, *tree8;
	AVLTreeNode *node1;

	 tree1 = CreateAVLTree("stdin");
	 PrintAVLTree(tree1);
	 FreeAVLTree(tree1);

	// you need to create the text file file1.txt
	// to store a set of items without duplicate items
	tree2 = CreateAVLTree("file1.txt"); 
	PrintAVLTree(tree2);

	tree3 = CloneAVLTree(tree2);
	PrintAVLTree(tree3);
	FreeAVLTree(tree2);
	FreeAVLTree(tree3);
	
	// Create tree4 
	tree4 = newAVLTree();
	j = InsertNode(tree4, 10, 10);
	for (i = 0; i < 15; i++) {
	j = InsertNode(tree4, i, i);
	if (j == 0) 
	printf("(%d, %d) already exists\n", i, i);
	}
	PrintAVLTree(tree4);

	node1 = Search(tree4,20,20);
	if (node1 != NULL)
	printf("key= %d value= %d\n",node1->key,node1->value);
	else 
	printf("Key 20 does not exist\n");

	for (i = 17; i > 0; i--) {
	j = DeleteNode(tree4, i, i);
	if (j == 0) 
		printf("Key %d does not exist\n",i);  
	PrintAVLTree(tree4);
	}
	FreeAVLTree(tree4);

	// Create tree5
	tree5 = newAVLTree();
	j = InsertNode(tree5, 6, 25);
	j = InsertNode(tree5, 6, 10);
	j = InsertNode(tree5, 6, 12);
	j = InsertNode(tree5, 6, 20);
	j = InsertNode(tree5, 9, 25);
	j = InsertNode(tree5, 10, 25);

	PrintAVLTree(tree5);
	//Create tree6
	tree6 = newAVLTree();
	j = InsertNode(tree6, 6, 25);
	j = InsertNode(tree6, 5, 10);
	j = InsertNode(tree6, 6, 12);
	j = InsertNode(tree6, 6, 20);
	j = InsertNode(tree6, 8, 35);
	j = InsertNode(tree6, 10, 25);
	PrintAVLTree(tree6);

	tree7 = AVLTreesIntersection(tree5, tree6);
	tree8 = AVLTreesUnion(tree5,tree6);
	PrintAVLTree(tree7);
	PrintAVLTree(tree8);

	return 0; 
}