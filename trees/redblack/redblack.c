#include <stdio.h>
#include <stdlib.h>

#define COLOR_BLACK 0
#define COLOR_RED   1
typedef struct rbnode{
   struct rbnode *parent;
   //left is children[0], right is children[1]
   struct rbnode *children[2];
   int color;
   int data;
}rbnode_t;

typedef struct rbtree{
   rbnode_t *root;
   int count;
}rbtree_t;

rbtree_t *rbtree_create(){
   rbtree_t *new_rbtree = malloc(sizeof(rbtree_t));
   new_rbtree->root = NULL;
   new_rbtree->count = 0;
   return new_rbtree;
}

rbnode_t *rbnode_create(int data){
   rbnode_t *new_rbnode = malloc(sizeof(rbnode_t));
   new_rbnode->parent = new_rbnode->children[0] = 
        new_rbnode->children[1] = NULL;
   new_rbnode->color = COLOR_RED;
   new_rbnode->data = data;
   return new_rbnode;
}

void rbtree_insert(rbnode_t **root, rbnode_t *new_node){
   if( (*root) == NULL ){
      (*root) = new_node;
      return;
   }else{
      new_node->parent = (*root);

      int dir = (*root)->data < new_node->data;

      rbtree_insert( &(*root)->children[dir], new_node );
   }
}


void main(){
   rbtree_t *rt = rbtree_create();
   for(int i = 0; i < 10; i++){
      rbtree_insert(&rt->root, rbnode_create(i));
   }
}
