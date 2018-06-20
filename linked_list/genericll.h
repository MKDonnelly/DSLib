#pragma once 

#include <stdlib.h>
#include <stdio.h>

//TODO Model this off of the linux kernel list implementation 
//TODO Use size_t to be more portable (specifically for Zeros)

/*			Generic Linked List
   These functions comprise a data structure that is a greatly
   generalized linked list. An Generic Linked List (hereby abbreviated
   as GLL) has been designed to manage a linked list of structures
   of unknown size.  In contrast to some linked list implementations
   where data is stored in a void* in a node struct for the linked list,
   the data structures are the nodes. This means that this can be used
   to manage a linked list of any type of structure, subject to the only
   constraint that the first member of the linked list must be a pointer
   to a struct of the same type for use by these functions.

   The macros preceeding each function allows easier use of ALLs.
   Additionally, there are several other macros that allow easy processing.
*/

//Structs to be put in the list put this at
//the head of the structure.
typedef struct list_head{
   struct list_head *next;
}list_head_t;

typedef struct list{
   list_head_t *head;
   int len;
   int ptr_offset;
}list_t;

#define list_head(list) \
        (list)->head
#define list_len(list) \
        (list)->len
#define list_ptroffset(list) \
        (list)->ptr_offset

#define list_create( struct_type, struct_ptr_member )\
   __list_create( __builtin_offsetof( struct_type, struct_ptr_member ) )
list_t *__list_create(int ptr_offset);

#define list_free( list, func ) \
   __list_free( &list, func )
void __list_free(list_t **self, void (*free_element)(void*));

#define list_add( list, element, index ) \
   __list_add(list, &((list)->head), element, index)
void __list_add(list_t *list, list_head_t **current, void *element, int index);

#define list_get(list, index, type) \
   (type *)__list_get(list, &((list)->head), index)
void *__list_get(list_t *list, list_head_t **current, int index);

//Given a pointer to the list_head_t member within a struct, as well
//as the containing list, get the head of the node.
#define list_ptrof(list, node, type) \
   (type*)((char*)node - (list)->ptr_offset)

#define list_foreach(list, loop_element) \
        for(list_head_t *loop_element = (list)->head;	\
            loop_element->next != NULL;			\
            loop_element = loop_element->next)

/*
//Powerful looping macro. This simplifies many different operations
//on a linked list.
#define list_foreach( list, element ) \
        for( typeof(list) element = list_get_node( list, 0 ); \
             element;                                       \
             element = element->next )

//Create a lambda function.
#define LAMBDA( rettype, params, func )  \
        ({                               \
           rettype __lambda__ params {   \
               func;                     \
           }                             \
           __lambda__;                   \
        })

//Removes the given element from the list and returns it.
//Returns NULL on error
#define list_rm_index( list, index )\
	__list_rm_index((list_head_t**)&list, index)
void *__list_rm_index( list_head_t **list, int index );

//Removes the node given a pointer to it
#define list_rm_node( list, node )\
	__list_rm_node((list_head_t**)&list, node)
void __list_rm_node( list_head_t **list, void *node );


//Returns the given node at index. Returns NULL on error
//This macro simplifies the syntax by automatically casting
//the return pointer and transforming list into (void**)&list
#define list_get_node( list, index ) \
	((typeof(list))__list_get_node( (list_head_t**)&list, index ))
void *__list_get_node( list_head_t **list, int index );

//Replaces the node at the given index with the new node.
//Returns the old node.
#define list_replaceby_index( list, new_node, index ) \
	__list_replaceby_index( (list_head_t**)&list, new_node, index )
void *__list_replaceby_index( list_head_t **list, void *new_node, int index );

#define list_replaceby_node( list, new_node, old ) \
	__list_replaceby_node( (list_head_t**)&list, new_node, old )
void *__list_replaceby_node( list_head_t **list, void *new_node, void *old );

//Returns the size of the generic linked list
#define list_size( list )\
        __list_size( (list_head_t**)&list )
int __list_size(list_head_t **list);*/
