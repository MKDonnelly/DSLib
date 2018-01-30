#include "stack.h"

void createStack( struct node **head ){
   createLL( head, 0 );
}

void pushStack( struct node **head, int item ){
   addItemLL( head, 0, item);
}

int popStack( struct node **head ){
   int val = getItemLL( head, 0 );
   rmItemLL( head, 0 );
   return val;
}

