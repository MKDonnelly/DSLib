#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstract_ll/abstract_ll.h"

typedef struct test{
   struct test *next;
   int e;
}test_t;

typedef struct mem{
   struct mem *next;
}mem_t;

void add_node_ll( void **list, void *element, int index){
   
   int cur_index = 0;
   mem_t **head = (mem_t**)list;

   //use next to step through the list
   mem_t *stepper = *head;

   //Move to the node just before the index we were given
   while( cur_index != (index-1) ){
      stepper = stepper->next;
      cur_index++;
   }

   //We are now at node index-1

   //Save the next node for later
   mem_t *next_node = stepper->next;
   printf("Address %x\n", element);
   stepper->next = element;
   stepper->next->next = next_node;
}

int main(){

   test_t *a = (test_t*)create_ll( 3, sizeof(test_t));

   test_t *new_el = (test_t*)malloc(sizeof(test_t));
   new_el->e = 111;

   printf("Address %x\n", new_el);

   //a->e = 10;
   //printf("%d\n", a->e);

   add_node_ll( &a, new_el, 1 );
   printf("%d\n", a->next->e);
/*
   a->next->e = 20;
   printf("%d\n", a->next->e);
   a->next->next->e = 30;
   printf("%d\n", a->next->next->e);
*/
   dealloc_ll( a );

   return 0;
}



/*
void add_node_ll( void *list, void *element, int index){
   
   int cur_index = 0;
   mem_t *head = (mem_t*)list;
   mem_t *new = (mem_t*)element;


   //Move to the node just before the index we were given
   while( cur_index != (index-1) ){
      head = head->next;
      cur_index++;
   }

   //We are now at node index-1

   //Save the next node for later
   mem_t *next_node = head->next;
   printf("Address %x\n", element);
   head->next = element;
   head->next->next = next_node;
}
*/

