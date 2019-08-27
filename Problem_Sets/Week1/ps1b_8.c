#include<stdio.h>

int main(int argc, char *argv[]){

	char *start, *end;

	if (argc == 2) {

		start = argv[1];
		end = argv[1];

		while (*end != '\0') {

			end++;
		}

        while (start != end) {

        	printf("%s\n", start);
			end--;
      		*end = '\0';
        }
	}
	
	return 0;
}
