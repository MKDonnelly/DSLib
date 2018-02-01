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


//Takes the list as an argument and sends it back 
//when returning. This seems strange, but seems better
//than having to cast the list to a void* every time.
void *add_node_ll( void *list, void *element, int index){

   //Adding an element to the head is a special case
   if( index == 0 ){
      mem_t *new_head = (mem_t*)element;
      new_head->next = list;
      return new_head;
   }
   
   int cur_index = 0;
   mem_t *head = (mem_t*)list;

   //use next to step through the list
   mem_t *stepper = head;

   //Move to the node just before the index we were given
   while( cur_index != (index-1) && stepper != NULL ){
      stepper = stepper->next;
      cur_index++;
   }


   //Verify that we really are at node index-1
   //Also catch the special case of adding to the end
   if( cur_index == (index-1) && stepper == NULL ){
      stepper = (mem_t*)element;
      stepper->next = 0;
   }else if( cur_index == (index-1) ){
      //Save the next node for later
      mem_t *next_node = stepper->next;
      stepper->next = element;
      stepper->next->next = next_node;
   }

   return (void*)head;
}
