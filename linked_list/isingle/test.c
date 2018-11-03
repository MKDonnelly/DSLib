#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include "slist.h"


typedef struct{
   slist_head_t next;
   int data;
}test_t;

void main(){
   slist_t *new_list = slist_create(test_t, next);

   for(int i = 0; i < 10; i++){
      test_t *t = malloc(sizeof(test_t));
      t->data = i;
      slist_add(new_list, t, 0);
   }
  
   for(test_t *node = slist_get(new_list, 0);
       node != NULL;
       node = slist_next(new_list, node) ){
      printf("Got %d\n", node->data);
   } 
}
