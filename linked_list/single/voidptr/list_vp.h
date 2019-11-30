#pragma once 

#include <stdlib.h>
#include <stdio.h>

typedef struct list_vptr_node{
   struct list_vptr_node *next;
   void *data;
}list_vptr_node_t;

typedef struct list_vptr{
   list_vptr_node_t *head;
   int elements;
}list_vptr_t;

#define list_vptr_len(list) (list)->elements

//Create a new vptr list
list_vptr_t *list_vptr_create();

//Frees a list
#define list_vptr_free(list, free_function) \
        __list_vptr_free(&(list)->head, free_function) 
void __list_vptr_free(list_vptr_node_t **list, void (*free_element)(void*));

//Adds an element to the list at the given position. If we
//hit the end without reaching the index, we place the 
//element at the end.
#define list_vptr_add(list, element, index) \
        __list_vptr_add(&(list)->head, element, index)
void __list_vptr_add(list_vptr_node_t **list, void *element, int index);

//Returns the i'th item in the list
#define list_vptr_get(list, index) \
        __list_vptr_get(&(list)->head, index)
void *__list_vptr_get(list_vptr_node_t **list, int index);

//Returns and removes the i'th item in the list
#define list_vptr_rm_index(list, index) \
        __list_vptr_rm_index(&(list)->head, index)
void *__list_vptr_rm_index(list_vptr_node_t **list, int index);

//Removes node given a pointer to the node
#define list_vptr_rm_node(list, node) \
        __list_vptr_rm_node(&(list)->head, node)
void __list_vptr_rm_node(list_vptr_node_t **list, void *node);

//Iterates through a list
#define list_iter(list, varname) \
        for(list_vptr_node_t *varname = (list)->head; \
            varname != NULL;                \
            varname = varname->next)
            
