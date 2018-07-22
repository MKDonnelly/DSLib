#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "genericll.h"

typedef struct{
   list_head_t next;
   int data;
}test_t;

void main(){
   list_t *new_list = list_create( test_t, next );

   test_t *new_item = malloc(sizeof(test_t));
   new_item->data = 111;

   list_add(new_list, new_item);
}
