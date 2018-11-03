#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hashchain.h"

void __assoc_key(hash_entry_t *entry, const char *key){
   entry->key = strdup(key);
}

static void key_free(hash_entry_t *entry){
   free(entry->key);
}

//Found on https://nullprogram.com/blog/2018/07/31/
static int triple_hash(int x){
   x ^= x >> 17;
   x *= 0xed5ad4bb;
   x ^= x >> 11;
   x *= 0xac4c1b51;
   x ^= x >> 15;
   x *= 0x31848bab;
   x ^= x >> 14;
   return x;
}

//Hashes a generic object by treating it as a sequence of bytes
//factor is used as a random seed: in this hash table, we will
//need sub-htables to have a different factor in order for the
//keys to go into different buckets.
static int generic_hash(void *object, int obj_len, int max, int factor){
   int acc = factor;
   for(int i = 0; i < obj_len; i++){
      acc += triple_hash( ((char*)object)[i] );
   }
   return triple_hash(acc) % max;
}

//Creates a generic hash table.
htable_t *__ghash_create(int buckets_per_level, int maxload, 
                         int minload, int hashentry_offset){
   htable_t *new_table = malloc(sizeof(htable_t));
   new_table->total_buckets = buckets_per_level;

   new_table->buckets = malloc(sizeof(bucket_t) * buckets_per_level);
   for(int i = 0; i < buckets_per_level; i++){
      new_table->buckets[i].list = __slist_create(hashentry_offset);
      new_table->buckets[i].type = 0;
   }

   new_table->entry_offset = hashentry_offset;
   new_table->max_load = maxload;
   new_table->min_load = minload;
   new_table->total_items = 0;
   new_table->hash = generic_hash; 
   new_table->hash_factor = rand();
   return new_table;
}


void ghash_insert(htable_t *table, void *new_element){
   hash_entry_t *entry = hash_member(new_element, table);
   int index = table->hash(entry->key, strlen(entry->key), 
                           table->total_buckets, table->hash_factor);

   //We assume inserting never fails, so we can increase the
   //item count for the table passed in.
   table->total_items++;

   //If type of the bucket is a list, append it...
   if( table->buckets[index].type == 0 ){
      slist_t *lst = table->buckets[index].list;
      slist_add(lst, entry, 0);
   }else if( table->buckets[index].type == 1 ){
      //else if it is a htable, recursively insert it.
      ghash_insert( table->buckets[index].table, new_element );
   }

   //After the element has been inserted, check to see if we
   //have exceeded the maximum load of the list and need to
   //convert it into a htable.
   if( table->buckets[index].type == 0 &&
      slist_len( table->buckets[index].list ) > table->max_load ){

      slist_t *copy_from = table->buckets[index].list;

      //Create new htable that is the same as the original
      table->buckets[index].table = __ghash_create(table->total_buckets, 
                                                   table->max_load,
                                                   table->min_load,
                                                   table->entry_offset);
      //Remove and place each element in the list into the new htable.
      //Keep in mind that once we remove the element from the list, we
      //cannot trust that the pointers within it refer to the list it
      //came from (i.e. we could have placed it into a new list). As a
      //result, moving to the next element by refering to hnode will break.
      for(hash_entry_t *hnode = slist_rm_index(copy_from,0);
          hnode != NULL;
          hnode = slist_rm_index(copy_from, 0) ){

          ghash_insert(table->buckets[index].table, hnode);
       }
       slist_free(copy_from, free);
   }
}

void *__ghash_get(htable_t *table, char *key){

   int index = table->hash(key, strlen(key), 
                           table->total_buckets, table->hash_factor);

   if( table->buckets[index].type == 0 ){
      slist_t *lst = table->buckets[index].list;
      for(hash_entry_t *hnode = slist_get(lst, 0); 
          hnode != NULL;
          hnode = slist_next(lst, hnode) ){

         if( strcmp(hnode->key, key) == 0 )
            return hnode;
      }
      //Key not in hash.
      return NULL;
   }else if( table->buckets[index].type == 1 ){
      //Hit a subtable, search within it.
      return __ghash_get( table->buckets[index].table, key );
   }
}

void *__ghash_remove(htable_t *table, char *key){
   int index = table->hash(key, strlen(key), 
                           table->total_buckets, table->hash_factor);

   if( table->buckets[index].type == 0 ){
      slist_t *lst = table->buckets[index].list;
      for(hash_entry_t *hnode = slist_get(lst, 0);
          hnode != NULL;
          hnode = slist_next(lst, hnode) ){

         if( strcmp(hnode->key, key) == 0 ){
            slist_rm_node(lst, hnode);
            key_free(hnode);
            return hnode;
         }
      }
      //Key not found
      return NULL;
   }else if( table->buckets[index].type == 1 ){
      void *item = __ghash_remove( table->buckets[index].table, key ); 

      //An item was removed only if we did not return NULL
      if( item != NULL )
          table->total_items--;
      return item;
   }
}
