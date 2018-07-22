#include <stdio.h>
#include <stdlib.h>

//Used when balancing the tree to tell where
//we are relative to the node added. This is intended
//to chain information back up the stack. This is a
//bitfield
#define IAM_NEWNODE	0x0
#define IAM_PARENT	0x1
#define GP_NEED_REBAL	0x2

typedef struct node{
   struct node *left, *right, *parent;
   int color;
   int data;
}node_t;

#define COLOR_BLACK	0
#define COLOR_RED	1

node_t *make_node(int val){
   node_t *n = malloc(sizeof(node_t));
   n->data = val; 
   n->left = n->right = NULL;
   n->color = COLOR_RED;
   return n;
}


void rb_insert(node_t **tree, node_t *new_node){
   int retval;
   if( *tree == NULL ){
      *tree = new_node;
      (*tree)->color = COLOR_RED;
   }else if( (*tree)->data < new_node->data ){
      retval = rb_insert( &((*tree)->right), new_node );
   }else if( (*tree)->data => new_node->data ){
      retval = rb_insert( &((*tree)->left), new_node );
   }
}



void main(){

   node_t *root = NULL;
   rb_insert( &root, make_node(5));
   rb_insert( &root, make_node(4));
   rb_insert( &root, make_node(6)); 

}
