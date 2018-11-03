#pragma once 

#include <stdlib.h>
#include <stdio.h>

typedef struct node{
   struct node *next;
   void *data;
}node_t;

typedef struct list{
   node_t *head;
   int elements;
}list_t;

//Statically initilize a list_t
#define list_init() (list_t){.head = NULL, .elements = 0}

//Iterates through a list
#define list_iter(list, varname) \
        for(node_t *varname = (list)->head; \
            varname != NULL;                \
            varname = varname->next)
            

//Creates a list
list_t *list_create();

//Frees a list
#define list_free(list, free_function) \
        __list_free(&(list)->head, free_function) \
        (list)->elements = 0;
void __list_free(node_t **list, void (*free_element)(void*));

//Adds an element to the list at the given position. If we
//hit the end without reaching the index, we place the 
//element at the end.
#define list_add(list, element, index) \
        __list_add(&(list)->head, element, index)
void __list_add(node_t **list, void *element, int index);

//Returns the i'th item in the list
#define list_get(list, index) \
        __list_get(&(list)->head, index)
void *__list_get(node_t **list, int index);

//Returns and removes the i'th item in the list
#define list_rm_index(list, index) \
        __list_rm_index(&(list)->head, index)
void *__list_rm_index(node_t **list, int index);

