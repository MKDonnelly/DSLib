#pragma once

typedef struct tnode{
   struct tnode *right;
   struct tnode *left;
   void *data;
}tnode_t;

tnode_t *make_node(void *data);
void insert_node(tnode_t **root, tnode_t *new_node);
