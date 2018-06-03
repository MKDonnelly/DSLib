#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

typedef struct item{
   struct item *next;
   int data;
}item_t;

item_t *make_item(int data){
   item_t *temp = malloc(sizeof(item_t));
   temp->data = data;
   return temp;
}

void main(){
   item_t *queue;
   printf("Putting ten data items into the queue\n");
   for(int i = 0; i < 10; i++){
      printf("Pushing %d\n", i);
      push_queue( queue, make_item(i));
   }

   printf("Now popping the data out...\n");
   for(int i = 0; i < 10; i++){
      item_t *temp = pop_queue(queue);
      printf("Popped %d\n", temp->data);
   }
   
}
