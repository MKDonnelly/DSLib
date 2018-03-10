#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void main(){
   node_t *head;
   create_ll( &head, 0 );

   node_t *newe = (node_t*)malloc(sizeof(node_t));
   newe->item = 10;
   add_node_ll( &head, newe, 0 );

   node_t *s = (node_t*)malloc(sizeof(node_t));
   s->item = 99;
   add_node_ll( &head, s, 0 );

   printf("%d %x %x\n", head->item, head, head->next);
//   printf("%d %x\n", head->next->item, head->next->next);

   dealloc_ll( &head );
}



