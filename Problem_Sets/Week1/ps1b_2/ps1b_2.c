
#include <stdio.h>
#include "Stack.h"

int main(void){

   int i, n, number;

   StackInit();

   printf("Enter a positive number: ");

   if (scanf("%d", &n) == 1 && (n > 0)){ // test if scanf successful and returns positive number

      for (i = 0; i < n; i++){
         printf("Enter a number: ");
         scanf("%d", &number);
         
         StackPush(number);
      }
      
      while (!StackIsEmpty()){
         
         printf("%d\n", StackPop());
      }
   }
   return 0;
}