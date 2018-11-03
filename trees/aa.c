#include <stdio.h>
#include <stdlib.h>

struct jsw_node{
   int data;
   int level;
   struct jsw_node *link[2];
};

struct jsw_node *nil;

int jsw_init(void){
   nil = malloc(sizeof *nil);

   if( nil == NULL )
      return 0;

   nil->level = 0;
   nil->link[0] = nil->link[1] = nil;
   return 1;
}

struct jsw_node *make_node(int data, int level){
   struct jsw_node *rn = malloc(sizeof *rn);

   if( rn == NULL )
      return NULL;

   rn->data = data;
   rn->level = level;
   rn->link[0] = rn->link[1] = nil;

   return rn;
}

struct jsw_node *skew(struct jsw_node *root){
   if( root->level != 0 ){
      if( root->link[0]->level == root->level ){
         struct jsw_node *save = root;

         root = root->link[0];
         save->link[0] = root->link[1];
         root->link[1] = save;
      }
      root->link[1] = skew(root->link[1]);
   }
   return root;
}

struct jsw_node *split(struct jsw_node *root){
   if( root->link[1]->link[1]->level == root->level && root->level != 0 ){
      struct jsw_node *save = root;

      root = root->link[1];
      save->link[1] = root->link[0];
      root->link[0] = save;
      ++root->level;
      root->link[1] = split(root->link[1]);
   }
   return root;
}

struct jsw_node *jsw_insert(struct jsw_node *root, int data){
   if( root == nil ){
      root = make_node(data, 1);
   }else{
      int dir = root->data < data;
      
      root->link[dir] = jsw_insert(root->link[dir], data);
      root = skew(root);
      root = split(root);
   }
   return root;
}

struct jsw_node *jsw_remove(struct jsw_node *root, int data){
   if( root != nil ){
      if( data == root->data ){
         if( root->link[0] != nil && root->link[1] != nil ){
            struct jsw_node *heir = root->link[0];
            while( heir->link[1] != nil )
               heir = heir->link[1];

            root->data = heir->data;
            root->link[0] = jsw_remove(root->link[0], root->data);
         }else{
            root = root->link[root->link[0] == nil];
         }
      }else{
         int dir = root->data < data;
         root->link[dir] = jsw_remove(root->link[dir], data);
      }
   }

   if( root->link[0]->level < root->level - 1 ||
       root->link[1]->level < root->level - 1 ){
      if( root->link[1]->level > --root->level )
         root->link[1]->level = root->level;

      root = skew(root);
      root = split(root);
   }
   return root;
}

void main(){
   jsw_init();
   struct jsw_node *root = nil;

   for(int i = 0; i < 7; i++)
      jsw_insert(root, i);
}
