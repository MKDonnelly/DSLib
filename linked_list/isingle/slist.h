#pragma once 

#include <stdlib.h>
#include <stdio.h>

//TODO also make a non-intrusive list that uses a void*
//     to the data. If we are just storing pointers or other
//     primitives, this would be simpler. In addition, create
//     an unrolled linked list.

//The Single Unordered List (slist) is intrusive.
//Place this structure into the data structure to
//be managed. 
typedef struct slist_head{
   struct slist_head *next;
}slist_head_t;

//Represents a slist
typedef struct slist{
   slist_head_t *head;
   int len;
   int ptr_offset;
}slist_t;

//Accessor macros for slist_t
#define slist_head(list) \
        (list)->head
#define slist_len(list) \
        (list)->len
#define slist_ptroffset(list) \
        (list)->ptr_offset

//Manages the slist_head_t's within a structure
//being managed. slist_container takes a pointer to
//a slist_head_t and returns a pointer to the
//user-defined structure. 
#define slist_container(list, node) \
   (void*)((char*)node - slist_ptroffset(list))

//Does the reverse of slist_container; given a
//user-defined structure, get a pointer to the
//contained slist_container
#define slist_member(list, node) \
   (slist_head_t*)( (char*)node + slist_ptroffset(list) )

//Given a node with a slist_head_t in it as well as a
//slist that the node is in, return the next node.
#define slist_next(list, node) \
        slist_container(list, (slist_member(list, node))->next)

//Iterates through a linked list. IT IS NOT SAFE TO CALL REMOVE
//ON THE ITEM, OR DO ANYTHING THAT ALTERS THE NEXT POINTER IN THE
//SLIST_HEAD_T. By calling slist_next, we assume that the node has
//a valid next pointer within the list. 
#define slist_iter(list, type, iter_name) \
        for(type iter_name = slist_get(list, 0); iter_name != 0; \
            iter_name = slist_next(list, iter_name) )

//Creates a slist_t and returns a pointer to it.
#define slist_create( struct_type, struct_ptr_member )\
   __slist_create( __builtin_offsetof( struct_type, struct_ptr_member ) )
slist_t *__slist_create(int ptr_offset);

//Destroys each element within the slist. The function passed
//in allows the user to free more than just the element, if needed.
#define slist_free( list, func ) \
   __slist_free( &list, func )
void __slist_free(slist_t **self, void (*free_element)(void*));


#define slist_append(list, element) \
        slist_add(list, element, slist_len(list) )
#define slist_add( list, element, index ) \
   __slist_add(list, &((list)->head), element, index)
void __slist_add(slist_t *list, slist_head_t **current, 
                  void *element, int index);

#define slist_get(list, index) __slist_get(list, &((list)->head), index)
void *__slist_get(slist_t *list, slist_head_t **current, int index);

#define slist_rm_index(list, index) \
        __slist_rm_index(list, &((list)->head), index)
void *__slist_rm_index(slist_t *self, slist_head_t **current,
                        int index);

#define slist_rm_node(list, node) \
        __slist_rm_node(list, &((list)->head), slist_member(list, node) )
void __slist_rm_node(slist_t *list, slist_head_t **current, 
                      slist_head_t *node);

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
