#pragma once 

#include <stdlib.h>
#include <stdio.h>

/*			Abstract Linked List
   These functions comprise a data structure that is a greatly
   abstracted linked list. An Abstract Linked List (hereby abbreviated
   as ALL) has been designed to manage a linked list of structures
   of unknown size.  In contrast to some linked list implementations
   where data is stored in a void* in a node struct for the linked list,
   the data structures are the nodes. This means that this can be used
   to manage a linked list of any type of structure, subject to the only
   constraint that the first member of the linked list must be a pointer
   to a struct of the same type for use by these functions.

   The macros preceeding each function allows easier use of ALLs.
*/

/*
//This takes a pointer to a linked list and initilizes
//it with the given number of elements with the given size.
//Passing a size of zero just nulls out the list. If invalid
//arguments are passed, return -1
#define create_ll( list, num_elements, element_size ) \
	__create_ll( (void**)&list, num_elements, element_size )
int __create_ll( void **list, int count, int element_size);


//Runs down a linked list and frees each node.
#define dealloc_ll( list ) \
	__dealloc_ll( (void**)&list )
void __dealloc_ll(void **list);


//Adds an element to the list at the given index
//Returns -1 on error
#define add_node_ll( list, element, index ) \
	__add_node_ll( (void**)&list, element, index )
int __add_node_ll( void **list, void *element, int index);


//Removes the given element from the list and returns it.
//Returns NULL on error
#define rm_node_ll( list, index )\
	__rm_node_ll( (void**)&list, index )
void *__rm_node_ll( void **list, int index );


//Returns the given node at index. Returns NULL on error
#define get_node_ll( list, index ) \
	__get_node_ll( (void**)&list, index )
void *__get_node_ll( void **list, int index );


//Replaces the node at index and returns the node that
//was there. Returns NULL on any error
#define exchg_node_ll( list, new_node, index ) \
	__exchg_node_ll( (void**)&list, new_node, index )
void *__exchg_node_ll(void **list, void *new_node, int index);


//Find the given node in the list, using the compare_function
//to determine if the element was found. The compare function should
//return 1 to indicate the the element passed to it is the correct one,
//0 else.
void *__find_node_ll( void **list, void *reference, int (*compare_function)(void*,void*) );

//Reverses the given linked list
void reverse_ll( void **list );

//Create a lambda function. This is a very useful construct when
//used with apply_op_ll since we can create small functions to
//pass to it.
#define LAMBDA( rettype, params, func )  \
        ({                               \
           rettype __lambda__ params {   \
               func;                     \
           }                             \
           __lambda__;                   \
        })


//Iterate through each member of the linked list and apply the
//given operation. The operator_function accepts a void pointer to 
//an element in the linked list and can change it in some way, once 
//it has been casted.
void __apply_op_ll( void **list, void (*operator_function)(void*) );

void reverse_ll(void **list);*/
