#include "abstract_ll.h"

//Internally used by create_ll
//NEVER used by outside code.
typedef struct mem{
   struct mem *next;
}mem_t;

//Creates a linked list
void *create_ll( int count, int element_size){

   //Initilize the head node. use next_node to
   //traverse the list without altering head.
   mem_t *head = (mem_t*)malloc( element_size );
   mem_t *next_node = head;
   count--;

   while( count-- > 0 ){
      //Allocate the *next pointer and jump through it.
      next_node->next = (mem_t*)malloc( element_size );
      next_node = next_node->next;
   }

   //Make sure the next pointer of the last node is null
   next_node->next = NULL;

   return (void*)head;
}


void dealloc_ll(void *list){

   mem_t *head = (mem_t*)list;
   mem_t *next = (mem_t*)list;
   
   while( head != NULL ){
      next = head->next;
      free( head );
      head = next;
   }
}
