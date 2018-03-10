#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
   int item;
   struct node *next;
} node_t;

//When passed two struct node pointers, this creates a linked list
//of the given size and returns the head and tail pointers.
void create_ll(node_t** list, int size);

//Deallocates the memory for the LL
void dealloc_ll(node_t** list);

int add_node_ll(node_t** list, node_t *element, int index);

node_t *rm_node_ll( node_t **list, int index );

node_t *get_node_ll( node_t **list, int index );

node_t *set_node_ll( node_t **list, node_t *new_node, int index );

node_t *find_node_ll(node_t **list, node_t *reference, int (*compare_function)(node_t*,node_t*));
