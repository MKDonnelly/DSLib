#pragma once 

#include <stdlib.h>
#include <stdio.h>

//Creates a linked list
void *create_ll( int count, int element_size);

//Deallocates each node of a linked list
void dealloc_ll(void *list);

//Adds an element to the list at the given index
//Does nothing if the index is invalid (i.e. adding
//an element to index 5 in a 3 element list)
void *add_node_ll( void *list, void *element, int index);
