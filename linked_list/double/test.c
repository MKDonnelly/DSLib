#include <stdio.h>
#include <stdlib.h>
#include "abstract_ll.h"

struct doublell{
   
};

struct item{
   struct item *next;
   int val;
};
typedef struct item item_t;

typedef struct mem{
   struct mem *next;
}mem_t;

/*
void reverse_ll( void **list ){
   mem_t **head = (mem_t**)list;
   mem_t *l = *head;

   mem_t *current = l;
   mem_t *last = NULL;

   while( current != NULL ){
      mem_t *temp = current->next;
      current->next = last;
      last = current;
      current = temp;
   } 
   (*head) = last;
}
*/
void main(){
   item_t *head;
   create_ll( head, 0, 0 );

   for(int i = 0; i < 10; i++){
      item_t *new_item = malloc(sizeof(item_t));
      new_item->val = i;
      add_node_ll( head, new_item, 0 );
   }

   reverse_ll( (void**)&head );

   __apply_op_ll( (void**)&head, LAMBDA( void, (void *element), 
                item_t *i = (item_t*)element;
                printf("%d\n", i->val );
              ));
}
