#pragma once 

#include <stdlib.h>
#include <stdio.h>

//Creates a linked list. Callers would do something like
//test_t *my_ll_head;
//create_ll( (void**)&my_ll_head, <number>, sizeof(test_t));
void create_ll( void **list, int count, int element_size);

//Deallocates each node of a linked list.
//Callers would do
//dealloc_ll( (void**)&my_ll_head );
void dealloc_ll(void **list);

//Adds an element to the list at the given index
//Does nothing if the index is invalid (i.e. adding
//an element to index 5 in a 3 element list)
int add_node_ll( void **list, void *element, int index);

//Removes the given element from the list and returns it.
void *rm_node_ll( void **list, int index );

//Returns the given node at index or null if it does
//not exist
void *get_node_ll( void **list, int index );

//Replaces the node at index and returns the node that
//was there
void *set_node_ll(void **list, void *new_node, int index);
