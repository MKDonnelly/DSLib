#pragma once 

#include <stdlib.h>
#include <stdio.h>

//Structs to be put in the list put this at
//the head of the structure. 
typedef struct dlist_head{
   struct dlist_head *next;
   struct dlist_head *prev;
}dlist_head_t;

//This represents a list as a whole.
typedef struct dlist{
   dlist_head_t *head;
   int len;
   int ptr_offset;
}dlist_t;

//Accessor macros for dlist_t
#define list_head( dlist ) \
        (dlist)->head
#define dlist_len( dlist ) \
        (dlist)->len
#define dlist_ptroffset( dlist ) \
        (dlist)->ptr_offset


//Given a list_head_t*, get the container it is in
#define dlist_container(type) \
        (type)_dlist_container
#define _dlist_container( list, node ) \
        ((char*)node - dlist_ptroffset(list))

#define dlist_member(dlist, node) \
   (dlist_head_t*)( (char*)node + dlist_ptroffset(dlist))


#define dlist_create( struct_name, struct_member ) \
        __dlist_create( __builtin_offsetof(struct_name, struct_member) )
dlist_t *__dlist_create(int ptr_offset);

#define dlist_free( list, func ) \
   __dlist_free( &list, func )
void __dlist_free(dlist_t **self, void (*free_element)(void*));


//Adds a new item to the given index.
#define dlist_append(dlist, element) \
        dlist_add(dlist, element, dlist_len(dlist))
#define dlist_add( dlist, element, index ) \
        __dlist_add(dlist, &((dlist)->head), element, index)
void __dlist_add(dlist_t *list, dlist_head_t **current, 
                 void *item, int index);


//__list_get returns a list_head_t*. Convert it
#define dlist_get(lst, type, index) \
        (dlist_node_cont( lst, __dlist_get(lst), type), index)
list_head_t *__dlist_get(dlist_t *list, int index);


//__list_rm works with list_head_t*, instead of void*.
//This converts it
#define dlist_rm_index(type) \
        (type)_dlist_rm_index
#define _dlist_rm_index( lst, index ) \
        __dlist_rm_index( lst, &((lst)->head), index )
void __dlist_rm_index(dlist_t *list, dlist_head_t **current, int index);

#define dlist_rm_node(lst, node) \
        __dlist_rm_node( lst, &((lst)->head), dlist_member(lst, node) )
void __dlist_rm_node(dlist_t *list, dlist_head_t **current,
                      dlist_head_t *node);
