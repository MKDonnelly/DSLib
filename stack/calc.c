#include <stdio.h>
#include <stdlib.h>
#include "../linked_list/genericll.h"
#include "stack.h"
#include <string.h>

typedef struct{
   char *item;
   list_head_t *next;
}calc_element_t;

#define MAX_BUF 100
void parse_expr( list_t *list, char *solve ){
   char *token;
   
   token = strtok(solve, " ");
   while( token != NULL ){
      calc_element_t *new_element = malloc(sizeof(calc_element_t));
      new_element->item = token;
      list_add(list, new_element, list_length(list) );
      token = strtok(NULL, " ");
   }
}

int priority(char input){
   switch(input){
      case '*':
      case '/':
         return 3;
      case '+':
      case '-':
         return 2;
      case '(':
         return 1;
   }
}

list_t *infix_to_postfix( list_t *tokens ){
   list_t *stack;
   INIT_STACK( stack, calc_element_t, next);
   list_t *postfix_list;
   INIT_LIST( postfix_list, calc_element_t, next);
 
   int length = list_length(tokens); 
   for(int i = 0; i < length; i++){
      calc_element_t *token = list_removeby_index( tokens, 0 );
      if( strstr( "*/+-()", token->item) == NULL ){
         list_add( postfix_list, token, list_length(postfix_list));
      }else if( strcmp(token->item, "(") == 0 ){
         stack_push( stack, token );
      }else if( strcmp(token->item, ")") == 0 ){
         calc_element_t *top_token = stack_pop( stack );
         while( strcmp( top_token->item, "(" ) != 0 ){
            list_add( postfix_list, top_token, list_length(postfix_list));
            top_token = stack_pop( stack );
         }
      }else{
         while( list_length( stack ) != 0 && 
                priority( ((calc_element_t*)stack_peek(stack))->item[0] ) > 
                priority( token->item[0] ) ){
            list_add( postfix_list, stack_pop(stack), 
                 list_length(postfix_list));
         }
         stack_push( stack, token );
      }
   }

   while( list_length(stack) != 0){
      list_add( postfix_list, stack_pop(stack), list_length(postfix_list));
   }

   return postfix_list;
}

int is_op(char *str){
   if( str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/' )
      return 1;
   return 0;
}

double postfix_eval(list_t *postfix_expr){
   list_t *temp;
   INIT_STACK(temp, calc_element_t, next);

   int len = list_length(postfix_expr);
   for(int i = 0; i < len; i++){
      calc_element_t *item = (calc_element_t*)list_removeby_index(postfix_expr, 0);
      if( is_op( item->item ) ){
         calc_element_t *second_number = stack_pop(temp);
         calc_element_t *first_number = stack_pop(temp);
         double first = atof(first_number->item);
         double second = atof(second_number->item);
         double result;
         if( item->item[0] == '+' ){
            result = first + second;
         }else if( item->item[0] == '-' ){
            result = first - second;
         }else if( item->item[0] == '*' ){
            result = first * second;
         }else{
            result = first / second;
         }
         free(second_number);
         free(first_number);
         calc_element_t *r = malloc(sizeof(calc_element_t));
         r->item = malloc(51);
         snprintf(r->item, 50, "%f", result);
         stack_push(temp, r);
      }else{
         stack_push(temp, item);
      }
   }
   return atof( ((calc_element_t*)stack_pop(temp))->item );
}


void main(){
   list_t *list;
   INIT_LIST( list, calc_element_t, next );
   char solve[] = "1 * 2 * ( 3 / 4 )";

   parse_expr( list, solve );

   list_t *postfix = infix_to_postfix(list);

   printf("Result is %f\n", postfix_eval(postfix));
}
