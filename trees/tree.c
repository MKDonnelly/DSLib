#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

tnode_t *make_node(int val){
   tnode_t *new = malloc(sizeof(tnode_t));
 
   new->val = val;
   new->left = new->right = NULL;

   return new;
}

void insert_node( tnode_t **root, tnode_t *new_node ){
   if( *root == NULL ){
      *root = new_node;
   }else if( new_node->val < (*root)->val ){
      insert_node( &((*root)->left), new_node);
   }else{
      insert_node( &((*root)->right), new_node);
   }
}

void print_level( tnode_t **root, int level ){
   if( *root == NULL ){
      printf("\n");
      return;
   }else if( level == 0 ){
//      printf("Node %x: Value: %d\n", (*root), (*root)->val);
      printf("%d ", (*root)->val);
   }else{
      print_level( &((*root)->left), level - 1);
      print_level( &((*root)->right), level - 1);
      printf("\n");
   }
}

void preorder(tnode_t *tree){
   if( tree != NULL ){
      printf("%d\n", tree->val);
      preorder( tree->left );
      preorder( tree->right );
   }
}

void inorder(tnode_t *tree){
   if( tree != NULL ){
      inorder( tree->left );
      printf("%d\n", tree->val);
      inorder( tree->right );
   }
}

void postorder(tnode_t *tree){
   if( tree != NULL ){
      postorder( tree->left );
      postorder( tree->right );
      printf("%d\n", tree->val);
   }
}

void main(){

   tnode_t *root = make_node(5);

   insert_node( &root, make_node(10) );
   insert_node( &root, make_node(2) );

   inorder(root);
}
