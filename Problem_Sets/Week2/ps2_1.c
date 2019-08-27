
/* Makes an array of 10 integers and returns a pointer to it */

int *makeArrayOfInts(void){ 
	
	int *arr = malloc(10 * sizeof(int));
	int i;

	for (i=0; i<10; i++) {

	arr[i] = i; 
	}
	
	return arr; 
}
