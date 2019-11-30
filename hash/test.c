#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashchain.h"

typedef struct{
   hash_entry_t hash_entry;
   int data;
}test_t;

test_t *create_entry(int data){
   test_t *new = malloc(sizeof(test_t));
   new->data = data;
   return new;
}

void main(){
   htable_t *table = ghash_create(100, 100000, 0, test_t, hash_entry);
   char key[] = "a";
   for(int i = 0; i < 26; i++){
      test_t *entry = create_entry(i);
      assoc_key(table, entry, key);
      key[0]++;
      ghash_insert(table, entry);
   }
}
