#include <stdio.h>
#include <stdlib.h>

typedef struct rb_node{
   int red, data;
   struct rb_node *children[2];
}rb_node_t;

typedef struct rb_tree{
   rb_node_t *root;
}rb_tree_t;

rb_tree_t *make_tree(){
   rb_tree_t *new_tree = malloc(sizeof(rb_tree_t));
   new_tree->root = NULL;
   return new_tree;
}

int is_red(rb_node_t *node){
   return node != NULL && node->red;
}

rb_node_t *make_node(int data){
   rb_node_t *new_node = malloc(sizeof(rb_node_t));
   new_node->data = data;
   new_node->red = 1;
   new_node->children[0] = new_node->children[1] = NULL;
   return new_node;
}

//Notation: |<letter>| = black, (<letter>) = red
//          {<letter>} = color does not matter

/*  Converts this ->>>>>>> Into this (for child == 1)
      |A|               |C|
      / \               / \
    |B| (C)           (A)  (E)
        / \           / \
      {D} (E)       |B| {D}


    Converts this ->>>>>>> Into this (for child == 0)
      |A|                |B|
      / \                / \
    (B) |C|            (D)  (A)
    / \                     /  \
   (D) {E}                {E}  |C|
*/
void single_rotate(rb_node_t **tree, int child){
   rb_node_t *new_root = (*tree)->children[child];
   rb_node_t *old_root = (*tree);

   //Move the child node under the new root to be under the
   //old root.
   old_root->children[child] = new_root->children[!child];

   //Move the new root to be the root of the tree.  Move the
   //old root as a child of the new root.
   new_root->children[!child] = old_root;
  
   old_root->red = 1;
   new_root->red = 0;

   *tree = new_root; 
}

/*  Convert this  ->>>> Into this  ->>>>> Then into this (for child == 0)

       |A|            |A|              |D|
       / \            / \              / \
     (B)  |C|       (D) |C|          (B)  (A)
       \            / \               \   /  \
       (D)        (B)  {F}           {E} {F} |C|
       /  \         \
     {E}  {F}      {E}

    Convert this ->>>>>> Into this  ->>>>>> Then into this (for child == 1)

      |A|               |A|                |D|
      / \               / \                / \
    |B| (C)           |B| (D)           (A)   (C)
        /                 / \           / \   /
       (D)              {E} (C)      |B| {E} {F}
       / \                  /  
     {E} {F}              {F}

//Note that the intermediate tree can be handled with single_rotate.
The first transformation can also be handled with single_rotate.
*/
void double_rotate(rb_node_t **tree, int child){
   //Do the first transformation
   single_rotate( &((*tree)->children[child]), !child );

   //Do the second transformation
   single_rotate( tree, child );
}


void __rb_insert(rb_node_t **root, int data){
   if( (*root) == NULL ){
      (*root) = make_node(data);
   }else if(data != (*root)->data){
      int dir = (*root)->data < data;
      __rb_insert(&((*root)->children[dir]), data);

      if( is_red( (*root)->children[dir] ) ){
         //Case 1: current node is black, with two children red
         if( is_red( (*root)->children[!dir] ) ){
            (*root)->red = 1;
            (*root)->children[0] = (*root)->children[1] = 0;

         //Case 2: Child is red and grandchild on same side is red.
         //        Fix using a single rotation around the opposite way
         //        (e.g. there are two consecutive red nodes on the left,
         //        rotate to the left to balance it out)
         }else if( is_red( (*root)->children[dir]->children[dir] ) ){
            single_rotate( root, dir );

         //Case 3: Child is red and the grandchild on the other side is red
         //        Fix using a double rotation towards the other way.
         }else if( is_red( (*root)->children[dir]->children[!dir] ) ){
            double_rotate( root, dir );
         }
      }
   }
}

void rb_insert(rb_tree_t *tree, int data){
   __rb_insert(&(tree->root), data);

   //Root must always be black
   tree->root->red = 0;
}

/*void __rb_remove(rb_node_t *tree, int data){
   if( tree == NULL ){
      //Data not found
      return;
   }else if( tree->data == data ){
      //remove node
      return;
   }else{
      int dir = tree->data < data;
      __rb_remove( tree->children[dir], data );

      if( 

   }
}*/

//0 = Removed node was red, so we do not need rebalancing
//1 = Node to remove is black. Leave it and rebalance to
//    change it to red.
int __rb_remove(rb_node_t **root, int data){

   rb_node_t *droot = *root;
   if( droot->data == data ){
      if( droot->red ){
         if( droot->children[0] == NULL && droot->children[1] == NULL){
            free(*root);
            *root = NULL;
         }else if( droot->children[0] == NULL || 
                   droot->children[1] == NULL ){
            *root = droot->children[ droot->children[0] == NULL ];
            free(droot);
         }else{
            rb_node_t *heir = droot->children[0];
            while( heir->children[1] != NULL )
               heir = heir->children[1];
            droot->data = heir->data;
            __rb_remove(&heir, heir->data);      
         }
         
         return 0;
      }else if( !droot->red ){
         //We cannot remove the black node right now.
         //Furthur up the tree, we will restructure to
         //change it into a red node, and then remove it.
         return 1;
      }
   }else{
      int dir = droot->data < data;
      int retval = __rb_remove( &(droot->children[dir]), data );

      //This should only run at most once. It happens when we
      //need to restructure the tree so that a black node turns
      //into a red node.
      if( retval == 1 ){
         //There are 4 cases where we need to flip the color of
         //a black node.

         //Case 1:
         //       R             B
         //      / \    ->     / \
         //     B   B         R   R
         if( droot->red && !droot->children[0] && !droot->children[1] ){
            droot->red = 0;
            droot->children[0]->red = droot->children[1]->red = 1;
            __rb_remove( &(droot->children[dir]), data );
            return 0;
         }else if( droot->red && droot->children[0]->red != 
                    droot->children[1]->red ){
           //Case 2: Parent is red, one child is red, and the 
           //        other is black. Do a single rotation to make the
           //        red node the new root.
           //We use !dir, since we had to have come from the black node
           //so !dir must be the red one.
           single_rotate( &droot->children[!dir], !dir );

           __rb_remove( &droot, data );
           return 0;
         }
      }
   }
}

void rb_remove(rb_tree_t *tree, int data){
   __rb_remove(&(tree->root), data);
   tree->root->red = 0;
}

void main(){
   rb_tree_t *root = make_tree();

   for(int i = 0; i < 3; i++)
      rb_insert(root, i);

   rb_remove(root, 0);
   rb_remove(root, 1);
}
