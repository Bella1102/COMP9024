#include <stdio.h>

int main(void){
	
	char catdog[] = {'a', 'c', 'd', 'g', 'o','t'};
	
	int count = 0;
	int i, j, k, m, n, p;
	
	for(i = 0; i < 6; i++)
		for(j = 0; j < 6; j++)
			for(k = 0; k < 6; k++)
				for(m = 0; m < 6; m++)
					for(n = 0; n < 6; n++)
						for(p = 0; p < 6; p++){
							
							if(i != j && i != k && i != m && i != n && i != p
							    && j != k && j != m && j != n && j != p
							    && k != m && k != n && k != p 
							    && m != n && m != p && n != p){
								
								printf("%c%c%c%c%c%c\n", catdog[i], catdog[j], catdog[k], catdog[m], catdog[n], catdog[p]);
								count++;
							}
						}
	printf("%d\n", count);
	
	return 0;
}