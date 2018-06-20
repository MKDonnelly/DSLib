#include <stdio.h>
#include <stdlib.h>

typedef struct node{
   struct node *left, *right;
   int bfactor;
   int data;
}node_t;

node_t *make_node(int data){
   node_t *n = malloc(sizeof(node_t));
   n->data = data;
   return n;
}

void insert_avl(node_t **tree, node_t *node){
   if( *tree == NULL ){
      *tree = node;
      (*tree)->left = (*tree)->right = NULL;
      (*tree)->bfactor = 0;
   }else if( (*tree)->data < node->data ){
      insert_avl( &((*tree)->right), node );
   }else if( (*tree)->data > node->data ){
      insert_avl( &((*tree)->left), node );
   }
}

void remove_avl(node_t **tree, int val){
   if( (*tree)->data == val ){
      if( (*tree)->left == NULL && (*tree)->right == NULL ){
         free( *tree );
         *tree = NULL;
      }else if( (*tree)->left != (*tree)->right ){
         node_t *temp = (*tree);
         (*tree) = (*tree)->left == NULL ? (*tree)->right : (*tree)->left;
         free(temp);
      }else{
         
      }
   }else if( (*tree)->data < val ){
      remove_avl( &((*tree)->right), val );
   }else if( (*tree)->data > val ){
      remove_avl( &((*tree)->left), val );
   }
}

void main(){
   
}
