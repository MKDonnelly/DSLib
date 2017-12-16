#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "stack.h"
#include "queue.h"

int main(){

   struct node *head;
   createQueue( &head );
/*
   printf("%d\n", getSizeLL(&head));
   addItemLL( &head, 0, 1);
   printf("%d\n", getSizeLL(&head));
   addItemLL( &head, 1, 2);
   printf("%d\n", getSizeLL(&head));
   addItemLL( &head, 2, 3);
   printf("%d\n", getSizeLL(&head));
   addItemLL( &head, 3, 4);
   printf("%d\n", getSizeLL(&head));
*/

   addItemQueue(&head, 1);
   addItemQueue(&head, 2);
   addItemQueue(&head, 3);
   addItemQueue(&head, 4);

   printf("%d\n", getItemQueue(&head));
   printf("%d\n", getItemQueue(&head));
   printf("%d\n", getItemQueue(&head));
   printf("%d\n", getItemQueue(&head));

   printLL( &head );

/*
   for(int i = 0; i < 5; i++){
      addItemQueue( &head, i );
   }*/

   return 0;
}


