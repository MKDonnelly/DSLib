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

/*
void *rm_node_ll( void *list, int index){
   if( index == 0 ){
      
   }
}*/

int main(){

   test_t **a;
   test((void**)a);

/*
   test_t *a = (test_t*)create_ll( 3, sizeof(test_t));

   a->e = 10;
   a->next->e = 20;
   a->next->next->e = 30;
   
   printf("%d %d %d\n", a->e, a->next->e, a->next->next->e);

   test_t *new_el = (test_t*)malloc(sizeof(test_t));
   new_el->e = 111;

   a = add_node_ll( a, new_el, 3 );
   printf("%d %d %d %d\n", a->e, a->next->e, a->next->next->e, a->next->next->next->e);

   dealloc_ll( a );
*/
   return 0;
}

