#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

typedef struct item{
    struct item *next;
    char c; 
}item_t;

item_t *create_item(char c){
   item_t *temp = malloc(sizeof(item_t));
   temp->c = c;
   return temp;
}

void main(){
   item_t *stack = NULL;
   char check[] = "()()()()()";
   int check_len = strlen(check);
   
   int valid_str = 1;
   for(int i = 0; i < check_len && valid_str; i++){
      if( check[i] == '(' ){
         stack_push( stack, create_item(check[i]));
      }else if( check[i] == ')' ){
         item_t *poped = stack_pop( stack );
         if( poped == NULL ){
            valid_str = 0;
            printf("FAILED on character %d\n", i);
            printf("%s\n", check);
            for(int j = 0; j < i - 1; j++)
               printf("~");
            printf("^\n");
         }
      }
   }
   if( stack != NULL){
      printf("FAILED: expecting terminating \')\' in input\n");
      printf("%s\n", check);
      for(int i = 0; i < check_len; i++)
         printf("~");
      printf("^\n");
   }else if( valid_str ){
      printf("String is balanced!\n");
   }
}
