#include <stdio.h>
#include <stdlib.h>
#include "gheap.h"

typedef struct{
   int data;
}test_t;

int test_compare(size_t *element1, size_t *element2){
   if( ((test_t*)element1)->data < ((test_t*)element2)->data )
      return 1;
   return 0;
}

void main(){
   srand(time(NULL));
   heap_t *new_heap = heap_create(test_compare);

   for(int i = 0; i < 9; i++){
      test_t *new_test = malloc(sizeof(test_t));
      new_test->data = rand();
      heap_add(new_heap, new_test);
   }

   for(int i = 0; i < 9; i++){
      test_t *ret = (test_t*)rm_top(new_heap);
      printf("%d\n", ret->data);
   }
}
