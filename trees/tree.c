#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

tnode_t *make_node(void *data){
   tnode_t *new = malloc(sizeof(tnode_t));
 
   new->data = data;
   new->left = new->right = NULL;

   return new;
}


void insert_node( tnode_t **root, tnode_t *new_node, ){
   if( *root == NULL ){
      *root = new_node;
      new_node->left = new_node->right = NULL;
   }else if( new_node->val < (*root)->val ){
      insert_node( &((*root)->left), new_node);
   }else if( new_node->val > (*root)->val ){
      insert_node( &((*root)->right), new_node);
   }
}

tnode_t *search_node( tnode_t **root, int val){
   if(*root == NULL){
      return NULL;
   }else if( (*root)->val == val ){
      return (*root);
   }else if( (*root)->val < val ){
      return search_node( &((*root)->right), val);
   }else if( (*root)->val > val){
      return search_node( &((*root)->left), val);
   }
}

tnode_t *find_min(tnode_t **root){
   if( (*root) == NULL ){
      return NULL;
   }else if( (*root)->left == NULL ){
      return (*root);
   }else{
      return find_min(&((*root)->left));
   }
}

tnode_t *find_max(tnode_t **root){
   if( (*root) == NULL ){
      return NULL;
   }else if( (*root)->right == NULL ){
      return (*root);
   }else{
      return find_max(&((*root)->right));
   }
}

void foreach_in_tree(tnode_t **tree, void (*function)(tnode_t*)){
   if( *tree != NULL ){
      function( *tree );
      foreach_in_tree( &((*tree)->left), function);
      foreach_in_tree( &((*tree)->right), function);
   }
}

void delete_node(tnode_t **tree, int item){
   if( *tree == NULL ){
      return;
   }else if( (*tree)->val == item ){
      if( (*tree)->right == NULL && (*tree)->left == NULL){
         //Zero children, simple delete the node
         free( *tree );
         *tree = NULL;
      }else if( !(*tree)->right != !(*tree)->left ){
         tnode_t *node;
         if( (*tree)->right != NULL ){
            node = (*tree)->right;
         }else{
            node = (*tree)->left;
         }
         free( *tree ):
         *tree = node;
      }else{

      }
   }else if( (*tree)->val < item ){
      delete_node( &((*tree)->right), item);
   }else if( (*tree)->val > item ){
      delete_node( &((*tree)->left), item);
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

void print_node(tnode_t *node){
   printf("Got node %d\n", node->val);
}

void main(){

   tnode_t *root = make_node(5);

   for(int i = 0; i < 5; i++)
      insert_node( &root, make_node(i));

   for(int i = 6; i < 10; i++)
      insert_node( &root, make_node(i));
   inorder(root);

   foreach_in_tree(&root, print_node);
}
