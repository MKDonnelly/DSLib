#include <stdio.h>
#include <stdlib.h>
//TODO clean up code
//TODO move rotation code into its own file since it is the
//       same for rb/avl trees.  Any format-specific modifications
//       (change balance for AVL, change colors for rb) can be wrapped
//       into a function along with the generic tree rotations.

//TODO make this generic
//TODO use *links[2] instead of left/right
typedef struct node{
   struct node *left, *right;
   int bfactor;
   int data;
}node_t;

node_t *make_node(int data){
   node_t *n = malloc(sizeof(node_t));
   n->data = data;
   n->left = n->right = NULL;
   n->bfactor = 0;
   return n;
}

int height_of(node_t *tree){
   if( tree == NULL || (tree->left == NULL && tree->right == NULL) ){
      return 0;
   }else{
      int left = tree->left == NULL ? 0 : height_of(tree->left) + 1;
      int right = tree->right == NULL ? 0 : height_of(tree->right) + 1;
      return left > right ? left : right;
   }
}

/* Converts this ->>>>>>>>>  Into this
    |first|                   |second|
         \                     /   \
        |second|          |first|  |third|
            \
           |third|
*/
void simple_rotate_left(node_t **tree){
   if( (*tree)->bfactor > 1 ){
      node_t *first = *tree;
      node_t *second = (*tree)->right;
      node_t *third = (*tree)->right->right;

      *tree = second;
      first->right = second->left;
      second->left = first;

      //update balance factors. 
      second->bfactor -= 1;
      first->bfactor -= 2;
   }
}

/* Converts this ->>>>>>>> Into this then calls simple_rotate_left
     |first|              |first| 
        \                    \
       |second|             |third|
        /    \              /  \
     |third|  |sr|         |tl| |second|
       / \                        / \
     |tl| |tr|                 |tr|  |sr|
*/


void rotate_left(node_t **tree){
   if( (*tree)->bfactor == 2 && (*tree)->right->bfactor == -1 ){
      node_t *first = *tree;
      node_t *second = (*tree)->right;
      node_t *third = (*tree)->right->left;

      first->right = third;
      second->left = third->right;
      third->right = second;

      //update balance factor
      second->bfactor = 0;
      third->bfactor = 1;
   }
   simple_rotate_left(tree);
}

/*Converts this ->>>>>>>> into this    
        |first|            |second|
          /                 /   \
     |second|           |third| |first|
        /
    |third|
*/
void simple_rotate_right(node_t **tree){
   if( (*tree)->bfactor < -1 ){
      node_t *first = *tree;
      node_t *second = (*tree)->left;
      node_t *third = (*tree)->left->left;

      *tree = second;
      first->left = second->right;
      second->right = first;

      //update balance factors. 
      second->bfactor += 1;
      first->bfactor += 2;
   }
}


/* Converts this ->>>>>>>> Into this then calls simple_rotate_left
         |first|               |first| 
          /                    /
       |second|             |third|
        /    \              /     \
       |sl|  |third|     |second| |tr|
              / \           / \
           |tl| |tr|     |sl|  |tl|
*/
void rotate_right(node_t **tree){
   if( (*tree)->bfactor == -2 && (*tree)->left->bfactor == 1 ){
      node_t *first = *tree;
      node_t *second = (*tree)->left;
      node_t *third = (*tree)->left->right;

      first->left = third;
      second->right = third->left;
      third->left = second;

      //update balance factor
      second->bfactor = 0;
      third->bfactor = -1;
   }
   simple_rotate_right(tree);
}


//Returns net change in the height of the tree returned.
int insert_avl(node_t **tree, node_t *node){
   if( *tree == NULL ){
      *tree = node;

      //By inserting this new tree, an additional edge was added
      //(the +1). In addition, the height changed by the height of
      //the new tree.
      return height_of(*tree) + 1;
   }else if( (*tree)->data < node->data ){
      int retval = insert_avl( &((*tree)->right), node );

      //update balance factor. the change in height
      //is propagated back to us
      (*tree)->bfactor += retval;
      rotate_left(tree);
      if( (*tree)->bfactor == 0 )
         return 0;
      return retval;
   }else if( (*tree)->data > node->data ){
      int retval = insert_avl( &((*tree)->left), node );

      (*tree)->bfactor -= retval;
      rotate_right(tree);
      if( (*tree)->bfactor == 0)
         return 0;
      return retval;
   }
}

int remove_avl(node_t **tree, int val){
   if( (*tree)->data == val ){
      if( (*tree)->left == NULL && (*tree)->right == NULL ){
         //no children
         free( *tree );
         *tree = NULL;
 
         //Tree is 1 shorter
         return 1;
      }else if( ((*tree)->left == NULL && (*tree)->right != NULL) ||
                ((*tree)->left != NULL && (*tree)->left == NULL )){
         //one child
         free(*tree);
         //promote the one child to be the new root of this local tree
         (*tree) = (*tree)->left == NULL ? (*tree)->right : (*tree)->left;

         //reduced height by 1
         return 1;
      }else{
         //two children. Replace removed node with the right node, and
         //then insert the left node into this tree. The left node will
         //always go to the left most node in the right tree.
         node_t *right = (*tree)->right;
         node_t *left = (*tree)->left;
         free(*tree);
         *tree = right;
         insert_avl( tree, left );
         
         //We remove a node, which means the height decreases by 1.
         return height_of(*tree) - 1;
      }
   }else if( (*tree)->data < val ){
      int retval = remove_avl( &((*tree)->right), val );

      (*tree)->bfactor -= retval;
      if( (*tree)->bfactor == 0 )
         return 0;
      return retval;
   }else if( (*tree)->data > val ){
      int retval = remove_avl( &((*tree)->left), val );

      (*tree)->bfactor += retval;
      if( (*tree)->bfactor == 0)
         return 0;
      return retval;
   }
}

void main(){
   node_t *tree = NULL;

   for(int i = 0; i < 10; i++){
      insert_avl(&tree, make_node(i));
   }
}
