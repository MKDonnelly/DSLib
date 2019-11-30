#include <stdio.h>
#include <stdlib.h>

struct jsw_node{
   int red, data;
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

struct jsw_node *jsw_double(struct jsw_node *root, int dir){
   root->link[!dir] = jsw_single(root->link[!dir], !dir);
   return jsw_single(root, dir);
}

int jsw_rb_assert(struct jsw_node *root)
{
    int lh, rh;

    if (root == NULL)
    {
        return 1;
    }
    else
    {
        struct jsw_node *ln = root->link[0];
        struct jsw_node *rn = root->link[1];

        /* Consecutive red links */
        if (is_red(root))
        {
            if (is_red(ln) || is_red(rn))
            {
                puts("Red violation");
                return 0;
            }
        }

        lh = jsw_rb_assert(ln);
        rh = jsw_rb_assert(rn);

        /* Invalid binary search tree */
        if ((ln != NULL && ln->data >= root->data) || (rn != NULL && rn->data <= root->data))
        {
            puts("Binary tree violation");
            return 0;
        }

        /* Black height mismatch */
        if (lh != 0 && rh != 0 && lh != rh)
        {
            puts("Black violation");
            return 0;
        }

        /* Only count black links */
        if (lh != 0 && rh != 0)
        {
            return is_red(root) ? lh : lh + 1;
        }
        else
        {
            return 0;
        }
    }
}

struct jsw_node *make_node(int data){
   struct jsw_node *rn = malloc(sizeof *rn);
   
   if( rn != NULL ){
      rn->data = data;
      rn->red = 1;
      rn->link[0] = NULL;
      rn->link[1] = NULL;
   }
   return rn;
}

struct jsw_node *jsw_remove_balance(struct jsw_node *root, int dir, int *done){
   struct jsw_node *p = root;
   struct jsw_node *s = root->link[!dir];

   if( is_red(s) ){
      root = jsw_single(root, dir);
      s = p->link[!dir];
   }

   if( s != NULL ){
      if( !is_red(s->link[0]) && !is_red(s->link[1])){
         if( is_red(p) )
            *done = 1;
         
         p->red = 0;
         s->red = 1;
      }else{
         int save = p->red;
         int new_root = (root == p);
         if( is_red(s->link[!dir]) )
            p = jsw_single(p, dir);
         else
            p = jsw_double(p, dir);

         p->red = save;
         p->link[0]->red = p->link[1]->red = 0;

         if( new_root )
            root = p;
         else
            root->link[dir] = p;
         *done = 1;
      }
   }
   return root;
}


struct jsw_node *jsw_insert_r(struct jsw_node *root, int data){
   if( root == NULL ){
      root = make_node(data);
   }else if(data != root->data){
      int dir = root->data < data;
      root->link[dir] = jsw_insert_r(root->link[dir], data);

      if( is_red(root->link[dir]) ){
         if( is_red(root->link[!dir]) ){
            //case 1: root is black, two children are red
            root->red = 1;
            root->link[0]->red = root->link[1]->red = 0;
         }else{
            //case 2: current node is red, sibling is not red
            //case 3: same as 2, but instead of the left child, it is
            //        the right child
            if( is_red(root->link[dir]->link[dir]) ){
               root = jsw_single(root, !dir);
            }else if( is_red(root->link[dir]->link[!dir]) ){
               root = jsw_double(root, !dir);
            }
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
         if( root->link[0] == NULL || root->link[1] == NULL){
            struct jsw_node *save = root->link[root->link[0] == NULL];
            
            //case 0: one one child
            if( is_red(root) ){
               *done = 1;
            }else if( is_red(save) ){
               save->red = 0;
               *done = 1;
            }
            free(root);
            return save;
         }else{
            struct jsw_node *heir = root->link[0];

            while(heir->link[1] != NULL)
               heir = heir->link[1];

            root->data = heir->data;
            data = heir->data;
         }

         dir = root->data < data;
         root->link[dir] = jsw_remove_r(root->link[dir], data, done);
         if( ! *done )
            root = jsw_remove_balance(root, dir, done);
      }
   }
   return root;
}

int jsw_remove(struct jsw_tree *tree, int data){
   int done = 0;
   tree->root = jsw_remove_r(tree->root, data, &done);
   if( tree->root != NULL )
      tree->root->red = 0;
   return 1;
}

int jsw_remove_top(struct jsw_tree *tree, int data){
   if( tree->root != NULL ){
      struct jsw_node head = {0}, *p, *q, *g, *f = NULL;
      int dir = 1;
      
      q = &head;
      g = p = NULL;
      q->link[1] = tree->root;

      //search and push red down
      while(q->link[dir] != NULL ){
         int last = dir;
         
         //update helpers
         g = p, p = q;
         q = q->link[dir];
         dir = q->data < data;

         //save found node
         if( q->data == data )
            f = q;

         //push the red node down
         if( !is_red(q) && !is_red(q->link[dir]) ){
            if( is_red(q->link[!dir])){
               p = p->link[last] = jsw_single(q, dir);
            }else if( !is_red(q->link[!dir]) ){
               struct jsw_node *s = p->link[!last];

               if( s != NULL ){
                  if( !is_red(s->link[!last]) && !is_red(s->link[last]) ){
                     //color flip
                     p->red = 0;
                     s->red = 1;
                     q->red = 1;
                  }else{
                     int dir2 = g->link[1] == p;
                     if( is_red(s->link[last]) )
                        g->link[dir2] = jsw_double(p, last);
                     else if( is_red(s->link[!last] ) )
                        g->link[dir2] = jsw_single(p, last);

                     q->red = g->link[dir2]->red = 1;
                     g->link[dir2]->link[0]->red = 0;
                     g->link[dir2]->link[1]->red = 0;
                     
                  }
               }
            }
         }         
      } 

     if( f != NULL ){
        f->data = q->data;
        p->link[p->link[1] == q] = q->link[p->link[0] == NULL];
        free(q);
     }

     tree->root = head.link[1];
     if( tree->root != NULL )
        tree->root->red = 0;

   }
   return 1;
}


void main(){

   struct jsw_tree tree;
   jsw_insert(&tree, 10);
   jsw_insert(&tree, 11);
   jsw_insert(&tree, 12);
   jsw_insert(&tree, 13);

   jsw_remove(&tree, 13);
   jsw_remove(&tree, 11);

   printf("%d\n", jsw_rb_assert(tree.root));
}
