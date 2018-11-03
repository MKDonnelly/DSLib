#include <stdio.h>
#include <stdlib.h>
//TODO clean up code
//TODO move rotation code into its own file since it is the
//       same for rb/avl trees.  Any format-specific modifications
//       (change balance for AVL, change colors for rb) can be wrapped
//       into a function along with the generic tree rotations. Make a
//       generic, intrusive structure to add to each node and can be
//       generically manipulated.

//Balance factor = sizeof(right_tree) - sizeof(left_tree)

#define XOR(first, second) ( !(first) != !(second) )

//TODO make this generic
typedef struct node{
   struct node *children[2];
   int bfactor;
   int data;
}node_t;

node_t *make_node(int data){
   node_t *n = malloc(sizeof(node_t));
   n->data = data;
   n->children[0] = n->children[1] = NULL;
   n->bfactor = 0;
   return n;
}


/* Converts this ->>>>>>>>>  Into this    for dir == 1
    |first|                   |second|
         \                     /   \
        |second|          |first|  |third|
            \
           |third|

  Converts this ->>>>>>>> into this        for dir == 0
        |first|            |second|
          /                 /   \
     |second|           |third| |first|
        /
    |third|
*/

void single_rotate(node_t **tree, int dir){
      node_t *new_root = (*tree)->children[dir];
      node_t *old_root = (*tree);

      //Move the child node under the new root to be under the
      //old root.
      old_root->children[dir] = new_root->children[!dir];

      //move the new root to be the root of the tree. Move the
      //old root as a child of the new root.
      new_root->children[!dir] = old_root;
  
      //adjust heights
      old_root->bfactor -= 2;
      new_root->bfactor -= 1;

      *tree = new_root;
}


/* Converts this ->>>>>>>> Into this       for dir == 1
     |first|              |first| 
        \                    \
       |second|             |third|
        /    \              /  \
     |third|  |sr|         |tl| |second|
       / \                        / \
     |tl| |tr|                 |tr|  |sr|

   Converts this ->>>>>>>> Into this       for dir == 0
         |first|               |first| 
          /                    /
       |second|             |third|
        /    \              /     \
       |sl|  |third|     |second| |tr|
              / \           / \
           |tl| |tr|     |sl|  |tl|
*/

void double_rotate(node_t **tree, int dir){
   single_rotate( &((*tree)->children[dir]), !dir );
   single_rotate( tree, dir );
}

void rebalance(node_t **tree, int dir){
   node_t *n = (*tree)->children[dir];
   int bal = dir == 0 ? -1 : 1;

   if( n->bfactor == bal ){
      single_rotate(tree, dir);
   }else{
      double_rotate(tree, dir);
   }
}


//Returns net change in the height of the tree returned.
int insert_avl(node_t **tree, node_t *node){

   if( *tree == NULL ){
      *tree = node;
      return 1;
   }else{
      int dir = (*tree)->data < node->data;
      int retval = insert_avl( &((*tree)->children[dir]), node );

      //Still more balancing to do
      if( retval ){
         (*tree)->bfactor += dir == 0 ? -1 : 1;
         if( abs( (*tree)->bfactor ) > 1 )
            rebalance(tree, dir);
      }

      return (*tree)->bfactor == 0 ? 0 : 1;
   }
}


/*
int remove_avl(node_t **tree, int val){

   //found node
   if( (*tree)->data == val ){
      //Case 1: Node has no children, so just delete it
      if( (*tree)->children[0] == NULL && (*tree)->children[1] == NULL ){
         free(*tree);
         *tree = NULL;

         //return the delta of the height 
         return 1;

      //Case 2: One child is null and the other is not.
      }else if( XOR((*tree)->children[0], (*tree)->children[1]) ){
         node_t *temp = (*tree);
         (*tree) = (*tree)->children[0] == NULL ? (*tree)->children[1] :
                                                  (*tree)->children[0];
         free(temp);

         //reduced height by 1
         return 1;

      //Case 3: Node to be deleted has two children. Take the right node,
      //        promote it to root, and then insert the left subtree.
      //        Note that we are inserting a whole tree (the left tree).
      }else{
         node_t *right = (*tree)->children[1];
         node_t *left = (*tree)->children[0];
         free(*tree);
         *tree = right;
         insert_avl( tree, left );

         //We remove a node, which means the height decreases by 1.
         printf("Returning %d\n", height_of(*tree) - 1);
         return height_of(*tree) - 1;
      }
   }else{
      //Recursive case where the data has not been found
      int dir = (*tree)->data < val;
      int retval = remove_avl( &((*tree)->children[dir]), val);

      if( dir == 1 ){
         (*tree)->bfactor -= retval;
      }else{
         (*tree)->bfactor += retval;
      }
  
      return (*tree)->bfactor == 0 ? 0 : retval;
   }         
}*/


void main(){
   node_t *tree = NULL;
   for(int i = 0; i < 7; i++){
      insert_avl(&tree, make_node(i));
   }
}
