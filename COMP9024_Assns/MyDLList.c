
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NUM 2048

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like 

// data structures representing DLList

// data type for nodes
typedef struct DLListNode{
  
  int  value;  // value (int) of this list item 
  struct DLListNode *prev;  // pointer previous node in list
  struct DLListNode *next;  // pointer to next node in list
  
} DLListNode;

// data type for doubly linked lists
typedef struct DLList{
  
  int  size;      // count of items in list
  DLListNode *first; // first node in list
  DLListNode *last;  // last node in list
  
} DLList;

// create a new DLListNode
DLListNode *newDLListNode(int it){
  
  DLListNode *new;
  new = malloc(sizeof(DLListNode));
  assert(new != NULL);
  
  new->value = it;
  new->prev = new->next = NULL;
  return new;
}

// create a new empty DLList
DLList *newDLList(){
    
  DLList *L;
  L = malloc(sizeof (struct DLList));
  assert (L != NULL);
  
  L->size = 0;
  L->first = NULL;
  L->last = NULL;
  return L;
}

// 1. create a DLList from a text file
// put your time complexity analysis for CreateDLListFromFileDlist() here
// assume the number of integers from stdin or file is n. 
// The total number of primitives is 6+2+3n+1+n+3+5n+4= 9n + 12.
// Time complexity = O(n).
DLList *CreateDLListFromFileDlist(const char *filename){
  
  DLList *L = newDLList();
  DLListNode *head;
  DLListNode *previous;
  DLListNode *temp;
  int n, count = 0;
  int array[NUM] = {};
  

  if (strcmp(filename, "stdin") == 0){
    
    char *buff = (char*)malloc(NUM);
   
    while((NULL != fgets(buff, NUM, stdin) && strlen(buff) != 1)){
      
      array[count] = atoi(buff);
      count++;    
    }	
    free(buff);	
    
    for(int i = 0; i < count; i++){

      if (i == 0){

        head = newDLListNode(array[0]);
        previous = head;
      } else {

        temp = newDLListNode(array[i]);
        previous -> next = temp;
        temp -> prev = previous;
        previous = temp;
    
      }
    }
    L -> size = count;
    L -> first = head;
    L -> last = temp;
     
    return L;
  }
  else {
    
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL){
      printf("Can't open file or file doesn't exist.\n");
      exit(0);
    }

    while (fscanf(fp, "%d", &n) != EOF){
      
      array[count] = n;
      count++;    
    }
    fclose(fp);
    
    if (count == 0){
      
      printf("There is no content in this file.\n");
      exit(0);
    }

    for(int i = 0; i < count; i++){

      if (i == 0){

        head = newDLListNode(array[0]);
        previous = head;
      } else {

        temp = newDLListNode(array[i]);
        previous -> next = temp;
        temp -> prev = previous;
        previous = temp;
      }
    }
    L -> size = count;
    L -> first = head;
    L -> last = temp;
     
    return L;
  }
}

// 2. display items of a DLList
// put your time complexity analysis for printDDList() here
// assume n = u -> size. 
// The total number of primitives is 2+n+n+n+1 = 3n + 3.
// Time complexity = O(n).
void printDLList(DLList *u){
  
  assert(u != NULL);
  DLListNode *curr;
  
  for (curr = u -> first; curr != NULL; curr = curr -> next){
    
      printf("%d\n", curr -> value); // 换行\n 记得改回来
  }
  printf("\n");
}

// 3. clone a DLList
// put your time complexity analysis for cloneList() here
// assume n = u -> size. 
// The total number of primitives is 8+6n+3 = 6n + 11.
// Time complexity = O(n).
DLList *cloneList(DLList *u){

  DLList *L = newDLList();
  DLListNode *temp;
  DLListNode *temp2;
  DLListNode *p;
  assert (u != NULL);
  
  L -> first = newDLListNode(u -> first -> value);
  temp = L -> first;
  p = u -> first;
  while (p -> next!= NULL){

    p = p -> next;
    temp2 = newDLListNode(p -> value);
    temp -> next = temp2;
    temp2 -> prev = temp;
    temp = temp2;
  }
  L -> size = u -> size;
  L->last = temp;

  return L;
}

// 4. compute the union of two DLLists u and v
// put your time complexity analysis for setUnion() here
// assume n = u -> size, m = v -> size.
// The total number of primitives is 6+n+m+m*n+7*m*n+3 = 8mn + m + n + 9
// Time complexity = O(mn).
DLList *setUnion(DLList *u, DLList *v){

  DLList *L = newDLList();
  DLListNode *temp;
  DLListNode *p1;
  DLListNode *p2;
  int count = 0;
  assert (u != NULL && v != NULL);
  L = cloneList(u);

  if (u -> size == 0 && v -> size == 0 ){
    return u;
    
  } else if (u -> size == 0 && v -> size != 0){
    return v;
    
  } else if (u -> size != 0  && v -> size == 0){
    return u;

  } else {

    for (p1 = v -> first; p1 != NULL; p1 = p1 -> next){
      for(p2 = u -> first; p2 != NULL; p2 = p2 -> next){

        if (p1 -> value == p2 -> value){
          break;

        } else if (p2 -> value == u -> last -> value){
          temp = newDLListNode(p1 -> value);
          L -> last -> next = temp;
          temp -> prev =  L -> last;
          L -> last = temp;
          count++;
          
        } else {
            continue;
        }
      }
    }
  }
  L -> size = count + u -> size;
  L -> last = temp;

  return L;
}

// 5. compute the insection of two DLLists u and v
// put your time complexity analysis for intersection() here
// assume n = u -> size, m = v -> size.
// The total number of primitives is 7+m+m*n+7*m*n+3 = 8mn + m + 10
// Time complexity = O(mn).
DLList *setIntersection(DLList *u, DLList *v){

  DLList *L = newDLList();
  DLListNode *temp;
  DLListNode *current;
  DLListNode *p1;
  DLListNode *p2;
  int count = 0;
  assert (u != NULL && v != NULL);

  if (u -> size == 0 || v -> size == 0 ){
    return NULL;

  } else {

    for (p1 = u -> first; p1 != NULL; p1 = p1 -> next){
      for(p2 = v -> first; p2 != NULL; p2 = p2 -> next){

        if (count == 0 && p1 -> value == p2 -> value){

          L -> first = newDLListNode(p1 -> value);
          current = L -> first;
          count++;

        } else if (p1 -> value == p2 -> value){

          temp = newDLListNode(p1 -> value);
          current -> next = temp;
          temp -> prev = current;
          current = temp;
          count++;
        }
      }
    }
  }
  L -> size = count;
  L -> last = current;

  return L;
}

// 6. free up all space associated with list
// put your time complexity analysis for freeDLList() here
// assume n = L -> size. 
// The total number of primitives is 4+n+3n+1 = 4n + 5.
// Time complexity = O(n).
void freeDLList(DLList *L){
  
  assert(L != NULL);
  
  DLListNode *current, *previous;
  current = L -> first;
  
  while (current != NULL) {
    
    previous = current;
    current = current -> next;
    free(previous);
  }
  free(L);
}


int main(){
  
  DLList *list1, *list2, *list3, *list4;
  
  list1 = CreateDLListFromFileDlist("File1.txt");
  printDLList(list1);
  
  list2 = CreateDLListFromFileDlist("File2.txt");
  printDLList(list2);
  
  list3 = setUnion(list1, list2);
  printDLList(list3);
  
  list4 = setIntersection(list1, list2);
  printDLList(list4);
  
  freeDLList(list1);
  freeDLList(list2);
  freeDLList(list3);
  freeDLList(list4);
  
  printf("please type all the integers of list1\n");
  list1 = CreateDLListFromFileDlist("stdin");
   
  printf("please type all the integers of list2\n");
  list2 = CreateDLListFromFileDlist("stdin");
  
  list3 = cloneList(list1);
  printDLList(list3);

  list4 = cloneList(list2);
  printDLList(list4);
  
  freeDLList(list1);
  freeDLList(list2);
  freeDLList(list3);
  freeDLList(list4);

  return 0; 
}
