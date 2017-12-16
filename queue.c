#include <stdlib.h>
#include <stdio.h>
#include "linkedList.h"

void createQueue(struct node **head){
   createLL( head, 0 );
}

int getItemQueue( struct node **head ){
   int val = getItemLL( head, 0 );
   rmItemLL( head, 0 );
   return val;
}

void addItemQueue( struct node **head, int item ){
   addItemLL(head, getSizeLL(head), item );
}
