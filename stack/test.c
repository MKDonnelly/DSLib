#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

struct item{
    struct item *next;
    char c; 
};
typedef struct item item_t;

void main(){
   item_t *stack;
   char check[] = "()()()()()))))))";
   int check_len = strlen(check);
   
   int valid_str = 1;
   for(int i = 0; i < check_len && valid_str; i++){
      if( check[i] == '(' ){
         item_t *pushed_item = malloc(sizeof(item_t));
         pushed_item->c = '(';
         push_stack( stack, pushed_item );
      }else if( check[i] == ')' ){
         item_t *poped = pop_stack( stack );
         if( poped == NULL || poped->c != '(' ){
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
