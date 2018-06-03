#pragma once

#include <stdlib.h>

//Include this in a structure to use it within a generic linked list
typedef struct list_head{
   struct list_head *next;
}list_head_t;

//
typedef struct list{
   list_head_t *list_head;
   unsigned int total_elements;
   unsigned int offset_of_ptr; 
}list_t;

void __list_add(list_t *list, list_head_t **head, void *item, int pos);
void *__list_removeby_index(list_t *list, list_head_t **head, int pos);
void *__list_getby_index(list_t *list, list_head_t **head, int pos);

#define INIT_LIST( list, type, member ) \
        ({ (list) = malloc(sizeof(list_t)); \
           (list)->list_head = NULL;     \
           (list)->total_elements = 0;   \
           (list)->offset_of_ptr = __builtin_offsetof(type, member); \
         })
#define list_add( listptr, item, pos )\
        __list_add( listptr, &((listptr)->list_head), item, pos )
#define list_removeby_index( listptr, pos )\
        __list_removeby_index( listptr, &((listptr)->list_head), pos)
#define list_getby_index( listptr, pos )\
        __list_getby_index( listptr, &((listptr)->list_head), pos ) 
#define list_length( list ) ((list)->total_elements)

