#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "genericll.h"

typedef struct{
   int data;
   list_head_t *next;
}test_t;

void main(){

   list_t *t;
   INIT_LIST( t, test_t, next );

   test_t *a = malloc(sizeof(test_t));
   a->data = 111;
   list_add(t, a, 0);

   test_t *b = malloc(sizeof(test_t));
   b->data = 222;
   list_add(t, b, 0);


   test_t *first = list_removeby_index( t, 0 );
   test_t *second = list_removeby_index(t, 0);
   printf("%d\n", first->data);
   printf("%d\n", second->data);
}



