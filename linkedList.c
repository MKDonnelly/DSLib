#include <stdio.h>
#include <stdlib.h>

typedef struct node{
   int item;
   struct node *next;
} llNode;


//When passed two struct node pointers, this creates a linked list
//of the given size and returns the head and tail pointers.
//If 0 is passed as the size, head is set to NULL. This is 
//recognized by other functions as being a linked list 
//of size 0.
void createLL( struct node **head, int size){

   //A liked list of size 0 is done by setting
   //the *head pointer to null.
   if( size == 0 ){
      *head = NULL;
      return;
   }

   //Use cur to move down the linked list
   //while preserving the head pointer.
   struct node **cur = head;

   //Create the first node
   *cur = (llNode*)malloc(sizeof(llNode));

   //Take the current node, allocate memory for
   //the next node pointer, and jump through 
   //the pointer. Start at 1 since we already
   //created the first node.
   for(int i = 1; i < size; i++){

      //Allocate memory for the node
      (*cur)->next = (llNode*)malloc(sizeof(llNode));
  
      //Jump through the pointer
      cur = &( (*cur)->next );
   }   

   //Set the last next pointer to null to
   //indicate this is the end of the list
   (*cur)->next = 0;
}


//Deallocates the memory for the LL
void deallocLL(struct node **head){

    //To free a linked list, we get
    //a reference to the next node,
    //free the node we are sitting on,
    //jump to the next node, and repeat.
    struct node **cur = head;
    struct node **nextNode;

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
void printLL(struct node **head){

   struct node **cur = head;
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
int findItemLL( struct node **head, int item ){
 
   //Catch the edge case where a list of length
   //0 is passed in.
   if( *head == NULL)
      return -1;
 
   struct node **cur = head;
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

int setItemLL(struct node **head, int index, int item){

   struct node **cur = head;
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


void rmItemLL(struct node **head, int index){

   //Catch the case where we are removing the
   //first element from the list.
   if( index == 0 && *head != NULL){
      struct node *cur = *head;
      *head = (*head)->next;
      free( cur );
   }
   
   struct node **cur = head;
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
      struct node *itemToRemove = (*cur)->next;
      (*cur)->next = (*cur)->next->next;
      free( itemToRemove );
   }
}


void addItemLL(struct node **head, int index, int val){

   struct node **cur = head;
   int itemNumber = 0;
   while( itemNumber < (index-1) && (*cur)->next != NULL){
      cur = &( (*cur)->next );
      itemNumber++;
   }

   if( (*cur) == NULL ){
      *cur = (struct node*)malloc(sizeof(struct node));
      (*cur)->next = 0;
      (*cur)->item = val;
   }else{
      struct node *tmp = (*cur)->next;
      (*cur)->next = (struct node*)malloc(sizeof(struct node));
      (*cur)->next->next = tmp;
      (*cur)->next->item = val;
   }














/*
   //Catch the case where we are adding to the start
   //of the list
   if( index == 0 ){
      struct node *newFirst = (struct node*)malloc(sizeof(struct node));
      newFirst->next = *head;
      newFirst->item = val;
      *head = newFirst;      
      return;
   }

   int itemNumber = 0;
   struct node **cur = head;

   //In the general case, loop through the list until we are
   //just before where the item will be inserted.
   while( itemNumber < (index-1) && *cur != NULL ){
      *cur = (*cur)->next;
      itemNumber++;
   }
*/
   
 
}


int getItemLL( struct node** head, int index){

   if( *head == NULL )
      return 0;

   struct node **cur = head;
   int nodeNum = 0;
   while( nodeNum < index && (*cur)->next != NULL ){
      cur = &( (*cur)->next );
      nodeNum++;
   }
   return (*cur)->item; 
}

int getSizeLL( struct node **head ){

   int size = 0;
   struct node **cur = head;

   if( *cur == NULL )
      return 0;

   size++;
   while( (*cur)->next != NULL ){
      cur = &( (*cur)->next );
      size++;
   }

   return size;
}
