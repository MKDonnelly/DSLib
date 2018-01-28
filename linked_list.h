
#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
   int item;
   struct node *next;
} node_t;

//When passed two struct node pointers, this creates a linked list
//of the given size and returns the head and tail pointers.
void create_ll( node_t**, int);

//Deallocates the memory for the LL
void dealloc_ll(node_t **);

//Given a linked list, print it out
void print_ll(node_t **);

//Finds the given element in the linked list
int find_item_ll( node_t **, int );

//Sets the given item in the linked list
int set_item_ll( node_t **, int, int);

//Removes the node in the array
void rm_node_ll( node_t **, int);

//Adds the given element to the given index
int add_node_ll( node_t **, int, int);

//Gets the value at index
int get_item_ll( node_t **, int);

//Gets the size of the linked list
int get_size_ll( node_t **);
