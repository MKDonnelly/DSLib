#include <stdio.h>
#include <stdlib.h>

struct jsw_node{
   int data;
   int balance;
   struct jsw_node *link[2];
};

struct jsw_tree{
   struct jsw_node *root;
};

struct jsw_node *make_node(int data){
   struct jsw_node *new_node = malloc(sizeof(struct jsw_node));
   new_node->data = data;
   new_node->balance = 0;
   new_node->link[0] = new_node->link[1] = NULL;
   return new_node;
}

struct jsw_node *jsw_single(struct jsw_node *root, int dir){
   struct jsw_node *save = root->link[!dir];
   
   root->link[!dir] = save->link[dir];
   save->link[dir] = root;

   return save;
}

struct jsw_node *jsw_double(struct jsw_node *root, int dir){
   struct jsw_node *save = root->link[!dir]->link[dir];

   root->link[!dir]->link[dir] = save->link[!dir];
   save->link[!dir] = root->link[!dir];
   root->link[!dir] = save;

   save = root->link[!dir];
   root->link[!dir] = save->link[dir];
   save->link[dir] = root;

   return save;
}

void jsw_adjust_balance(struct jsw_node *root, int dir, int bal){
   struct jsw_node *n = root->link[dir];
   struct jsw_node *nn = n->link[!dir];

   if(nn->balance == 0){
         root->balance = n->balance = 0;
   }else if(nn->balance == bal){
      root->balance = -bal;
      n->balance = 0;
   }else{
      root->balance = 0;
      n->balance = bal;
   }
   nn->balance = 0;
}

struct jsw_node *jsw_insert_balance(struct jsw_node *root, int dir){
   struct jsw_node *n = root->link[dir];
   int bal = dir == 0 ? -1 : 1;

   if(n->balance == bal){
      root->balance = n->balance = 0;
      root = jsw_single(root, !dir);
   }else{
      jsw_adjust_balance(root, dir, bal);
      root = jsw_double(root, !dir);
   }
   return root;
}

struct jsw_node *jsw_insert_r(struct jsw_node *root, int data, int *done){
   if( root == NULL ){
      root = make_node(data);
   }else{
      int dir = root->data < data;
      root->link[dir] = jsw_insert_r(root->link[dir], data, done);

      if(! *done ){
         root->balance += dir == 0 ? -1 : 1;

         if( root->balance == 0 ){
            *done = 1;
         }else if( abs(root->balance) > 1 ){
            root = jsw_insert_balance(root, dir);
            *done = 1;
         }
      }
   }
   return root;
}

int jsw_insert(struct jsw_tree *tree, int data){
   int done = 0;
   tree->root = jsw_insert_r(tree->root, data, &done);
   return 1;
}

struct jsw_node *jsw_remove_balance(struct jsw_node *root, int dir, int *done){
   struct jsw_node *n = root->link[!dir];
   int bal = dir == 0 ? -1 : 1;

   if( n->balance == -bal ){
      root->balance = n->balance = 0;
      root = jsw_single(root, dir);
   }else if( n->balance == bal){
      jsw_adjust_balance(root, !dir, -bal);
      root = jsw_double(root, dir);
   }else{
      root->balance = -bal;
      n->balance = bal;
      root = jsw_single(root, dir);
      *done = 1;
   }
   return root;
}

struct jsw_node *jsw_remove_r(struct jsw_node *root, int data, int *done){
   if( root != NULL ){
      int dir;
      if( root->data == data ){
         if( root->link[0] == NULL || root->link[1] == NULL ){
            struct jsw_node *save;
  
            dir = root->link[0] == NULL;
            save = root->link[dir];
            free(root);

            return save;
         }else{
            struct jsw_node *heir = root->link[0];
 
            while(heir->link[1] != NULL )
               heir = heir->link[1];

            root->data = heir->data;
            data = heir->data;
         }
      }

      dir = root->data < data;
      root->link[dir] = jsw_remove_r(root->link[dir], data, done);

      if( ! *done ){
         root->balance += dir != 0 ? -1 : 1;

         if( abs(root->balance) == 1 ){
            *done = 1;
         }else if( abs(root->balance) > 1 ){
            root = jsw_remove_balance(root, dir, done);
         }
      }
   }
   return root;
}

int jsw_remove(struct jsw_tree *tree, int data){
   int done = 0;
   tree->root = jsw_remove_r(tree->root, data, &done);
   return 1;
}

void main(){
   struct jsw_tree tree;
   tree.root = NULL;

   for(int i = 0; i < 3; i++)
      jsw_insert(&tree, i);
}
