
#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
   int item;
   struct node *next;
} llNode;

//When passed two struct node pointers, this creates a linked list
//of the given size and returns the head and tail pointers.
void createLL( struct node**, int);

//Deallocates the memory for the LL
void deallocLL(struct node **);

//Given a linked list, print it out
void printLL(struct node **);

//Finds the given element in the linked list
int findItemLL( struct node **, int );

//Sets the given item in the linked list
int setItemLL(struct node **, int, int);

//Removes the element in the array
void rmItemLL(struct node **, int);

//Adds the given element to the given index
void addItemLL(struct node **, int, int);

//Gets the value at index
int getItemLL(struct node**, int);

//Gets the size of the linked list
int getSizeLL(struct node**);
