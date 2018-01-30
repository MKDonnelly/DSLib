#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

//When passed two struct node pointers, this creates a linked list
//of the given size and returns the head and tail pointers.
//If 0 is passed as the size, head is set to NULL. This is 
//recognized by other functions as being a linked list 
//of size 0.
void create_ll( node_t **head, int size){

   //A liked list of size 0 is done by setting
   //the *head pointer to null.
   if( size == 0 ){
      *head = NULL;
      return;
   }

   //Use cur to move down the linked list
   //while preserving the head pointer.
   node_t **cur = head;

   //Create the first node
   *cur = (node_t*)malloc(sizeof(node_t));

   //Take the current node, allocate memory for
   //the next node pointer, and jump through 
   //the pointer. Start at 1 since we already
   //created the first node.
   for(int i = 1; i < size; i++){

      //Allocate memory for the node
      (*cur)->next = (node_t*)malloc(sizeof(node_t));
  
      //Jump through the pointer
      cur = &( (*cur)->next );
   }   

   //Set the last next pointer to null to
   //indicate this is the end of the list
   (*cur)->next = 0;
}


//Deallocates the memory for the LL
void dealloc_ll(struct node **head){

    //To free a linked list, we get
    //a reference to the next node,
    //free the node we are sitting on,
    //jump to the next node, and repeat.
    node_t **cur = head;
    node_t **nextNode;

    while( *cur != NULL ){
        //Save the next node pointer
        nextNode = &( (*cur)->next );

        //Deallocate the current LL node
        free( *cur );

        //Jump to the next node
        cur = nextNode;
    }

    //Make sure the caller can tell that
    //the linked list passed in now has 
    //a size of 0.
    *head = NULL;
}


//Given a linked list, print it out
void print_ll(struct node **head){

   node_t **cur = head;
   int i = 0;

   //Keep going until what cur is pointing
   //to is null (i.e. we ran into the end)
   while( *cur != NULL ){    
      printf("Linked List Member #%d\n", i);
      printf("   item: %d\n", (*cur)->item);
      printf("   nextL 0x%x\n", (*cur)->next);
      cur = &( (*cur)->next );
      i++;
   }   
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

   while( (*cur)->item != item && (*cur)->next != NULL ){
      cur = &( (*cur)->next );
      nodeNum++;
   }

   //The item may not exist in the linked list
   if( (*cur)->item != item )
      return -1;
   else
      return nodeNum;
}

int set_item_ll(struct node **head, int index, int item){

   node_t **cur = head;
   int i = 0;

   while( i < index && *cur != NULL){
      cur = &( (*cur)->next );
      i++;
   }
   
   //We may have a large index than there
   //are items in the list
   if( i != index )
      return -1;
   else if( *cur != NULL)
      (*cur)->item = item;
}


void rm_node_ll(struct node **head, int index){

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


int add_node_ll( node_t **head, int index, int val){

   node_t **cur = head;
   int itemNumber = 0;

   //Loop until we are just before where we need to add the element.
   //So if we need to add an element to index 3, we would go to
   //index 2, and use that as firm ground to setup the new node.
   while( itemNumber < (index-1) && *cur != NULL && (*cur)->next != NULL){
      cur = &( (*cur)->next );
      itemNumber++;
   }

   //If we were not able to get into the correct spot,
   //return an error code. This is better than an application
   //thinking that the value is at a certain position, when
   //it is really not.
   if( itemNumber != (index-1) ){
      return -1;
   }else if( *cur == NULL ){
      node_t *tmp = (*cur)->next;
      (*cur)->next = (node_t*)malloc(sizeof(node_t));
      (*cur)->next->next = tmp;
      (*cur)->next->item = val;
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
