#include <stdio.h>
#include <stdlib.h>

struct jsw_node{
   int red;
   int data;
   struct jsw_node *link[2];
};

struct jsw_tree{
   struct jsw_node *root;
};

int is_red(struct jsw_node *root){
   return root != NULL && root->red == 1;
}

struct jsw_node *jsw_single(struct jsw_node *root, int dir){
   struct jsw_node *save = root->link[!dir];

   root->link[!dir] = save->link[dir];
   save->link[dir] = root;

   root->red = 1;
   save->red = 0;

   return save;
}

int jsw_rb_assert(struct jsw_node *root){
   int lh, rh;
   if( root == NULL ){
      return 1;
   }else{
      struct jsw_node *ln = root->link[0];
      struct jsw_node *rn = root->link[1];

      if( is_red(root) ){
         if( is_red(ln) || is_red(rn) ){
            puts("Red violation");
            return 0;
         }
      }

      lh = jsw_rb_assert(ln);
      rh = jsw_rb_assert(rn);

      if((ln != NULL && ln->data >= root->data) ||
         (rn != NULL && rn->data <= root->data) ){
         puts("Binary tree violation");
         return 0;
      }

      if( ln != 0 && rh != 0 && lh != rh){
         puts("Black violation");
         return 0;
      }

      if( lh != 0 && rh != 0 ){
         return is_red(root) ? lh : lh + 1;
      }else{
         return 0;
      }
   }
}

struct jsw_node *make_node(int data){
   struct jsw_node *rn = malloc(sizeof *rn);
   
   if( rn != NULL ){
      rn->data = data;
      rn->red = 1;
      rn->link[0] = rn->link[1] = NULL;
   }

   return rn;
}

struct jsw_node *jsw_insert_r(struct jsw_node *root, int data){
   if( root == NULL ){
      root = make_node(data);
   }else if( data != root->data ){
      int dir = root->data < data;
      root->link[dir] = jsw_insert_r(root->link[dir], data);

      if( is_red(root->link[dir]) ){
         if( is_red(root->link[!dir]) ){
            //case 1
            root->red = 1;
            root->link[0]->red = 0;
            root->link[1]->red = 0;
         }else{
            //case 2 & 3
            if( is_red(root->link[dir]->link[dir] ) )
               root = jsw_single(root, !dir);
            else
               root = jsw_double(root, !dir);
         }
      }
   }
   return root;
}

int jsw_insert(struct jsw_tree *tree, int data){
   tree->root = jsw_insert_r(tree->root, data);
   tree->root->red = 0;
   return 1;
}

struct jsw_node *jsw_remove_r(struct jsw_node *root, int data, int *done){
   if( root == NULL ){
      *done = 1;
   }else{
      int dir;
      if( root->data == data ){
         if( root->link[0] == NULL || root->link[1] == NULL ){
            struct jsw_node *save = root->link[root->link[0] == NULL];
            
            if( is_red(root) ){
               *done = 1;
            }else if( is_red(save) ){
               save->red = 0;
               *done = 1;
            }

            free(root);
            return save;
         }
      }else{
         struct jsw_node *heir = root->link[0];
         while(heir->link[1] != NULL)
            heir = heir->link[1];

         root->data = heir->data;
         data = heir->data;

      }
   }

   dir = root->data < data;
   root->link[dir] = jsw_remove_r(root->link[dir], data, done);

   if(!*done){
      root = jsw_remove_balance(root, dir, done);
   }

   return root;
}

int jsw_remove(struct jsw_tree *tree, int data){
   int done = 0;
   
   tree->root = jsw_remove_r(tree->root, data, &done );

   if( tree->root != NULL )
      tree->root->red = 0;

   return 1;
}

void main(){

}
