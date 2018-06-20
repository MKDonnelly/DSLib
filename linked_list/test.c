#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "genericll.h"

typedef struct{
   list_head_t *next;
   int data;
}test_t;

void main(){
   list_t *new_list = list_create( test_t, next );

   test_t *first = malloc(sizeof(test_t));
   first->data = 111;
   test_t *second = malloc(sizeof(test_t));
   second->data = 222;

   list_add(new_list, first, 0 );
   list_add(new_list, second, 1);

   list_foreach(new_list, e){
      test_t *element = list_ptrof(new_list, e, test_t);
      printf("Got %d\n", element->data);
   }

}
