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

int is_closing(char c){
   if( c == '}' || c == ']' || c == ')' )
      return 1;
   return 0;
}

int is_opening(char c){
   if( c == '{' || c == '[' || c == '(' )
      return 1;
   return 0;
}

int brackets_match(char b1, char b2){
   if( (b1 == '{' && b2 == '}') || (b1 == '}' && b2 == '{') )
      return 1;
   if( (b1 == '[' && b2 == ']') || (b1 == ']' && b2 == '[') )
      return 1;
   if( (b1 == '(' && b2 == ')') || (b1 == ')' && b2 == '(') )
      return 1;
   return 0;
}

void main(){
   item_t *stack = NULL;
   char check[] = "{()()[]()()}";
   int check_len = strlen(check);
   
   int valid_str = 1;
   for(int i = 0; i < check_len && valid_str; i++){
      if( is_opening(check[i]) ){
         stack_push( stack, create_item(check[i]));
      }else if( is_closing(check[i]) ){
         item_t *poped = stack_pop( stack );
         if( poped == NULL || !brackets_match(check[i], poped->c) ){
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
