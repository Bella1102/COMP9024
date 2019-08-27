#include<stdio.h>

#define MIN 10000
#define MAX 24999

int main(void){


	int a,b,c,d,e,n;
	for(n = MIN; n <= MAX; n++){
	
		a = (n/10000)%10;
		b = (n/1000)%10;
		c = (n/100)%10;
		d = (n/10)%10;
		e = n%10;

		if (4*n == 10000*e + 1000*d + 100*c +10*b +a ){
	
			printf("%d\n", n);
		}
	}
	return 0;
}
