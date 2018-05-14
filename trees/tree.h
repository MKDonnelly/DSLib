#pragma once

struct tnode{
   struct tnode *right;
   struct tnode *left;
   int val;
};
typedef struct tnode tnode_t;


tnode_t *make_node(int);
void insert_node(tnode_t**,tnode_t*);
