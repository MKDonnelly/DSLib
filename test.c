#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
//#include "stack.h"
//#include "queue.h"

int main(){

   node_t *head;
   create_ll( &head, 0 );

   add_node_ll( &head, 3, 10 );
   
   return 0;
}


