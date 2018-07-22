#pragma once 

#include <stdlib.h>
#include <stdio.h>

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
typedef struct sulist_head{
   struct sulist_head *next;
}sulist_head_t;

typedef struct sulist{
   sulist_head_t *head;
   int len;
   int ptr_offset;
}sulist_t;

#define sulist_head(list) \
        (list)->head
#define sulist_len(list) \
        (list)->len
#define sulist_ptroffset(list) \
        (list)->ptr_offset

//Given a pointer to the list_head_t member within a struct, as well
//as the containing list, get the head of the node.
#define sulist_container(list, node, type) \
   (type*)((char*)node - sulist_ptroffset(list))

#define sulist_ptrin(list, node) \
   (sulist_head_t*)( (char*)node + sulist_ptroffset(list) )


#define sulist_create( struct_type, struct_ptr_member )\
   __sulist_create( __builtin_offsetof( struct_type, struct_ptr_member ) )
sulist_t *__sulist_create(int ptr_offset);

#define sulist_free( list, func ) \
   __sulist_free( &list, func )
void __sulist_free(sulist_t **self, void (*free_element)(void*));

#define sulist_append(list, element) \
        sulist_add(list, element, sulist_len(list) )
#define sulist_add( list, element, index ) \
   __sulist_add(list, &((list)->head), element, index)
void __sulist_add(sulist_t *list, sulist_head_t **current, 
                  void *element, int index);

#define sulist_get(type) (type)_sulist_get
#define _sulist_get(list, index) __sulist_get(list, &((list)->head), index)
void *__sulist_get(sulist_t *list, sulist_head_t **current, int index);

#define sulist_rm_index(type) (type)_sulist_rm_index
#define _sulist_rm_index(list, index) \
        __sulist_rm_index(list, &((list)->head), index)
void *__sulist_rm_index(sulist_t *self, sulist_head_t **current,
                        int index);

#define sulist_rm_node(list, node) \
        __sulist_rm_node(list, &((list)->head), \
        (sulist_head_t*)((char*)node + sulist_ptroffset(list)))
void __sulist_rm_node(sulist_t *list, sulist_head_t **current, 
                      sulist_head_t *node);


//TODO This has one big flaw: if we insert the same element
//     into a different list during iteration, this will not
//     do what we want.  Instead, we should hold a temporary
//     pointer to the next element.
#define sulist_foreach(list, loop_element) \
        for(sulist_head_t *loop_element = (list)->head;	\
            loop_element != NULL;			\
            loop_element = loop_element->next)

/*
//Create a lambda function.
#define LAMBDA( rettype, params, func )  \
        ({                               \
           rettype __lambda__ params {   \
               func;                     \
           }                             \
           __lambda__;                   \
        })
*/
