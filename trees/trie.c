#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO Mark the end of a string in the node, else
//     we could end up deleting a valid key!
//TODO create a trie that can take an arbitrary
//     piece of data as a key and store another
//     arbitrary piece of data.

//only handles lower-case letter strings
typedef struct tnode{
   char c;
   struct tnode *children[128];
   void *data;
}tnode_t;

int char_to_index(char c){
   return c;
}

//When iterating down the string, the first character is the node
//we are on. The second character is the next node to jump to.
void insert_trie(tnode_t **root, char *str, void *data){

   if( str[0] == '\0' ){
      (*root)->data = data;
      return;
   } 

   tnode_t **child = &((*root)->children[char_to_index(str[0])]);
   if( *child == NULL ){
      tnode_t *new_node = malloc(sizeof(tnode_t));
      *child = new_node;
   }
 
   (*child)->c = str[0];
   insert_trie( child, str+1, data);
}

void *find_trie(tnode_t *root, char *key){
   if( root == NULL ){
      return NULL;
   }else if( key[0] == '\0' ){
      return root->data;
   }else{
      return find_trie(root->children[char_to_index(key[0])], key+1);
   }
}


//TODO make a reference count for each node to know when to delete
void rm_trie(tnode_t **root, char *key){
   if( (*root) == NULL ){
     return;
   }else if( key[0] == '\0' ){
     free( *root );
     *root = NULL;
   }else{
      rm_trie( &((*root)->children[char_to_index(key[0])]), key+1);

      int rm = 1;
      for(int i = 0; i < 26; i++){
         if( (*root)->children[i] != NULL )
            rm = 0;
      }
      
      if(rm){
         free(*root);
         *root = NULL;
      }
   }
}


tnode_t *create_trie(){
   tnode_t *new_trie = malloc(sizeof(tnode_t));
   new_trie->data = NULL; //this is root, it contains no data
   memset(new_trie->children, 0, sizeof(tnode_t*)*26);
   return new_trie;
}

int myf(int a){
   return a+1;
}

void main(){
   tnode_t *root = create_trie();

   for(int i = 0; i < 10; i++){
      char buf[20];
      snprintf(buf, 20, "%d", i);
      printf("%s, ", buf);
      printf("%d\n", myf(i));
      insert_trie(&root, buf, (void*)myf(i));
   }

   for(int i = 0; i < 10; i++){
      char b[20];
      snprintf(b, 20, "%d", i);
      printf("%d maps to %d\n", i, (int)find_trie(root, b));
   }
   
}
