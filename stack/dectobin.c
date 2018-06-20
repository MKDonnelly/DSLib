#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct digit{
   struct digit *next;
   int digit;
}digit_t;

digit_t *create_digit(int d){
   digit_t *new_digit = malloc(sizeof(digit_t));
   new_digit->digit = d;
   return new_digit;
}

void convert_base(int number, int base){
   digit_t *stack = NULL;
   char digits[] = "0123456789ABCDEF";
   while( number != 0 ){
      stack_push( stack, create_digit(number % base) );
      number /= base;
   }

   printf("In base %d: ", base);
   while( stack_size(stack) > 0 ){
      digit_t *d = stack_pop(stack);
      printf("%c", digits[d->digit]);
      free(d);
   }
}

void main(){
   int number = 12345;
   convert_base(number, 16);
}
