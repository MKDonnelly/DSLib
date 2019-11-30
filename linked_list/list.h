#pragma once

#include "./single/intrusive/list.h"

#define TYPE_SINGLE_INTRUSIVE 0
#define TYPE_SINGLE_VPTR      1
typedef struct list{
   char type;

   union{
      list_si_t *single_intrusive;
   };
}list_t;

#define list_create(list_in, newtype, ...) \
        CREATE_ ##newtype(list_in, __VA_ARGS__)

#define CREATE_TYPE_SINGLE_INTRUSIVE(list_in, ...) \
        do{							\
           list_in = malloc(sizeof(list_t));			\
           (list_in)->type = TYPE_SINGLE_INTRUSIVE;		\
           (list_in)->single_intrusive = list_si_create(__VA_ARGS__); \
        }while(0);

#define CREATE_TYPE_SINGLE_VPTR(list_in, variable_args) \
        do{							\
           list_in = malloc(sizeof(list_t));			\
           (list_in)->type = TYPE_SINGLE_VPTR;			\
           (list_in)->single_vptr = list_vptr_create();		\
        }while(0);

void list_add(list_t *l, void *element, int index);
void *list_rm_index(list_t *l, int index);
void list_rm_node(list_t *l, void *node);
void *list_get(list_t *l, int index);
int list_len(list_t *l);
int list_type(list_t *l);
void list_free(list_t *l, void (*free_node)(void*));
