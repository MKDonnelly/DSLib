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

//Find the given element in the list, using a compare function
//passed in.  Return null if it is not found.
void *find_node_ll( void **list, void *element, int (*compare_function)(void *first, void *second) ){

    mem_t **head = (mem_t**)list;
    mem_t *stepper = *head;

    while( stepper != NULL ){
       if( compare_function( stepper, element ) == 1 )
          return stepper;
       stepper = stepper->next;
    }
    return 0;
}

int comp( void *, void *element2){
   printf("%d\n", ((test_t*)element1)->e);
   if( ((test_t*)element1)->e > ((test_t*)element2)->e )
      return 1;
   else
      return 0;
}

int main(){

   test_t *element = (test_t*)malloc(sizeof(test_t));
   element->e = 11;
   test_t *el2 = (test_t*)malloc(sizeof(test_t));
   el2->e = 22;

   test_t *compare = (test_t*)malloc(sizeof(test_t));
   compare->e = 10;

   test_t *t;

   create_ll( (void**)&t, 0, sizeof(test_t));
   add_node_ll( (void**)&t, element, 0 );
   add_node_ll( (void**)&t, el2, 1);

//   test_t *removed = (test_t*)rm_node_ll( (void**)&t, 0 );
//   printf("%d %d\n", removed->e, removed->next);
   test_t *found_node = find_node_ll( (void**)&t, compare, comp );
   if( found_node )
      printf("%d %d\n", found_node->e, found_node->next );


   dealloc_ll( (void**)&t );


/*
   test_t *b = (test_t*)malloc(sizeof(test_t));
   b->e = 100;
   test_t *c = (test_t*)malloc(sizeof(test_t));
   c->e = 88;
   test_t *d = (test_t*)malloc(sizeof(test_t));
   d->e = 77;

   test_t *a;
   create_ll( (void**)&a, 0, sizeof(test_t));
   add_node_ll( (void**)&a, b, 0 );
   add_node_ll( (void**)&a, c, 1);

   test_t *temp = (test_t*)set_node_ll( (void**)&a, d, 1 );

   printf("%d %d\n", temp->e, temp->next );
   printf("%d %d\n", a->next->e, a->next->next);
   

   dealloc_ll( (void**)&a );
*/
   return 0;
}

