#include <stdio.h>
#include "generic_ll.h"

typedef struct item{
   struct item *next;
   int a;
   char b;
}item_t;

typedef struct mem{
   struct mem *next;
}mem_t;

void an_ll( void **list, void *element, int index){
   mem_t **head = (mem_t**)list;

   if( *head == NULL ){
      *head = element;
      (*head)->next = NULL;
   }else if( index == 0 ){
      //Replace the head node
      mem_t *temp = *head;
      (*head) = element;

      mem_t *new_head = (mem_t*)element;
      new_head->next = temp;
   }else{
      an_ll( (void**)&(*head)->next, element, index - 1 );
   }
}

void main(){

   item_t *first;
   create_ll( first, 0, sizeof(item_t));

   item_t *item = malloc(sizeof(item_t));
   item->a = 100;
   item_t *second = malloc(sizeof(item_t));
   second->a = 200;

   an_ll( (void**)&first, item, 0 );
   an_ll( (void**)&first, second, 1);

   printf("%x %d\n", first->next, first->a);

/*

   foreach_in_gll(first, node){
      printf("%x\n", node);
   }
  */ 
}
