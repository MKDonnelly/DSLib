#pragma once 

#include <stdlib.h>
#include <stdio.h>

//Creates a linked list
void *create_ll( int count, int element_size);

//Deallocates each node of a linked list
void dealloc_ll(void *list);
