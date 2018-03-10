#include <stdio.h>
#include <stdlib.h>
#include "abstract_ll.h"

typedef struct test{
   struct test *next;

   int a;
   char b;
   double c;
}test_t;

void main(){

   test_t *head;

   test_t *first = (test_t*)malloc(sizeof(test_t));
   first->a = first->b = first->c = 1;
   test_t *second = (test_t*)malloc(sizeof(test_t));
   second->a = second->b = second->c = 2;
   test_t *third = (test_t*)malloc(sizeof(test_t));
   third->a = third->b = third->c = 3;

   create_ll( allist(head), 0, sizeof(test_t));
   add_node_ll( allist(head), first, 0 );
   add_node_ll( allist(head), second, 0 );
   add_node_ll( allist(head), third, 0 );

   apply_op_ll( allist(head), LAMBDA( void, (void *item),
                  test_t *node = (test_t*)item;
                  printf("%d\n", node->a );
               ));
}
