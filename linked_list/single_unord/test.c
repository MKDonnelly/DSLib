#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "sulist.h"

typedef struct{
   sulist_head_t next;
   int data;
}test_t;

void main(){
   sulist_t *new_list = sulist_create(test_t, next);

   for(int i = 0; i < 3; i++){
      test_t *t = malloc(sizeof(test_t));
      t->data = i;
      sulist_add(new_list, t, i);
   }
   
   test_t *first = sulist_get(test_t*)(new_list, 1);
   printf("Got %d\n", first->data);


   sulist_rm_node(new_list, first);

   test_t *a = sulist_get(test_t*)(new_list, 1);
   printf("Got %d\n", a->data);

   sulist_free(new_list, free);
}
