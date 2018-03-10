#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

//Creates a linked list in a ring. Returns back the first
//(although it does not matter since it is a ring) node
//in the linked list. For size <= 0, *list is null. This
//is recognized as an empty list by the other functions below.
void create_ll( node_t **list, int size){

   //Indicate the list is empty with NULL 
   if( size <= 0 ){
      *list = NULL;
      return;
   }


   //Create the first node
   (*list) = (node_t*)malloc(sizeof(node_t));

   //Get a reference to the next node
   node_t *next_node = (*list);

   //Take the current node, allocate memory for
   //the next node pointer, and jump through 
   //the pointer. Start at 1 since we already
   //created the first node.
   for(int i = 1; i < size; i++){

      //Allocate memory for the next node
      next_node->next = (node_t*)malloc(sizeof(node_t));

      //Jump through the pointer
      next_node = next_node->next;
   }   

   //Set the last next pointer to the head
   //of this list 
   next_node->next = *list;
}


//Deallocates the memory for the ring linked list
void dealloc_ll(struct node **list){

    if( *list == NULL )
        return;

    node_t *cur = *list;
    node_t *nextNode;

    //To free a ring linked list, run down the list
    //until we wrap back  around to head.
    do{
        //Save the next node pointer
        nextNode = cur->next;

        //Deallocate the current LL node
        free( cur );

        //Jump to the next node
        cur = nextNode;
    }while( cur != *list );

    //Make sure the caller can tell that
    //the linked list passed now has 
    //a size of 0.
    *list = NULL;
}

//Given the ring linked list, add the given node to the index
//This is different from a regular NULL terminated list in that
//index is interpreted to be index % linked_list_size 
int add_node_ll( node_t **head, node_t *element, int index){

   if( element == NULL || index < 0 )
      return 0;

   if( *head == NULL && index == 0 ){
      *head = element;
      (*head)->next = element;
      return 0;
   }

   node_t *current_node = *head;
   int current_index = 0;

   //Loop until we are just before where we need to 
   //put the new node. Since this is a ring linked
   //list, there should be no null to run into.
   while( current_index < (index-1) ){
      current_node = current_node->next;
      current_index++;
   }

   if( current_index == 0 ){
            
   }

   //Place the new node
   node_t *next_node = current_node->next;
   current_node->next = element;
   current_node->next->next = next_node;
}





//Search the linked list for the given item
//Return -1 if the item does not exist in the list.
int find_item_ll( struct node **head, int item ){
 
   //Catch the edge case where a list of length
   //0 is passed in.
   if( *head == NULL)
      return -1;
 
   node_t **cur = head;
   int nodeNum = 0;

   do{
      cur = &( (*cur)->next );
      nodeNum++;
   }while( (*cur)->item != item && (*cur)->next != *head );

   //The item may not exist in the linked list
   if( (*cur)->item != item )
      return -1;
   else
      return nodeNum;
}


int set_item_ll(struct node **head, int index, int item){

   node_t **cur = head;
   int i = 0;

   do{
      cur = &( (*cur)->next );
      i++;
   }while( i < index && *cur != *head);
   
   //We may have a large index than there
   //are items in the list
   if( i != index )
      return -1;
   else if( *cur != NULL )
      (*cur)->item = item;
}


node_t *rm_node_ll(node_t **head, int index){

   //Catch the case where we are removing the
   //first element from the list.
   if( index == 0 && *head != NULL){
      node_t *cur = *head;
      *head = (*head)->next;
      free( cur );
   }
   
   node_t **cur = head;
   int curIndex = 0;

   //Loop until we are on the node just before
   //the one we want to remove.
   while( curIndex < (index-1) && *cur != NULL){
      cur = &( (*cur)->next );
      curIndex++;
   }

   //We may have hit the end of the list
   //due if sizeof(linkedList) < index
   if( curIndex == (index-1)){
      node_t *itemToRemove = (*cur)->next;
      (*cur)->next = (*cur)->next->next;
      free( itemToRemove );
   }
}



int get_item_ll( node_t **head, int index){

   if( *head == NULL )
      return 0;

   node_t **cur = head;
   int nodeNum = 0;

   while( nodeNum < index && (*cur)->next != NULL ){
      cur = &( (*cur)->next );
      nodeNum++;
   }
   return (*cur)->item; 
}



int get_size_ll( node_t **head ){

   int size = 0;
   node_t **cur = head;

   if( *cur == NULL )
      return 0;

   size++;
   while( (*cur)->next != NULL ){
      cur = &( (*cur)->next );
      size++;
   }

   return size;
}
