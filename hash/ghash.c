#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../linked_list/single_unord/sulist.h"

typedef struct{
   sulist_head_t lst;
   char *key;
}hash_entry_t;

void assoc_key(hash_entry_t *entry, const char *key){
   entry->key = strdup(key);
}

void key_free(hash_entry_t *entry){
   free(entry->key);
}

//A generic hash function. Meant to take an
//arbirary piece of data and return a value
//from 0..max.  factor is meant to change how the 
//function hashes: we can pass a random number (and
//remember the random number) to create a family of
//generic hash functions.
int generic_hash(void *object, int obj_len, int max, int factor){
   int acc = 0;
   for(int i = 0; i < obj_len; i++, factor += 2){
      acc += ((char*)object)[i] * factor;
      acc %= max;
   }
   return acc < 0 ? -acc : acc;
}

//A table representing a generic hash.
typedef struct hashtbl{
   int max_load, minload;
   int entry_offset;

   int total_buckets;
   sulist_t **buckets;
   struct hashtbl **subtables;

   int hash_factor;
   int (*hash)(void *object, int obj_len, int max, int factor);
}hashtbl_t;

//Creates a generic hash table.
#define ghash_create(size, struct_type, struct_entry) \
        __ghash_create( size, __builtin_offsetof(struct_type,struct_entry))
hashtbl_t *__ghash_create(int buckets_per_level, int hashentry_offset){
   hashtbl_t *new_table = malloc(sizeof(hashtbl_t));
   new_table->total_buckets = buckets_per_level;

   new_table->buckets = malloc(sizeof(sulist_t) * buckets_per_level);
   new_table->subtables = malloc(sizeof(hashtbl_t*) * buckets_per_level);
   for(int i = 0; i < buckets_per_level; i++){
      new_table->buckets[i] = sulist_create(hash_entry_t, lst);
      new_table->subtables[i] = NULL;
   }

   new_table->entry_offset = hashentry_offset;
   new_table->hash = generic_hash; 
   new_table->hash_factor = rand();
   return new_table;
}


void ghash_insert(hashtbl_t *table, void *e){
   hash_entry_t *entry = (hash_entry_t*)((char*)e + table->entry_offset);
   int index = table->hash(entry->key, strlen(entry->key), 
                           table->total_buckets, table->hash_factor);

   if( table->subtables[index] == NULL ){
      sulist_t *lst = table->buckets[index];
      sulist_append(lst, entry);
   }else{
      ghash_insert( table->subtables[index], e );
   }
}

#define ghash_get( type ) \
   (type) _ghash_get
#define _ghash_get(table, key) \
   ((char*)__ghash_get(table, key) - (table)->entry_offset)
void *__ghash_get(hashtbl_t *table, char *key){
   int index = table->hash(key, strlen(key), 
                           table->total_buckets, table->hash_factor);
   if( table->subtables[index] == NULL ){
      sulist_t *lst = table->buckets[index];
      sulist_foreach( lst, e ){
         hash_entry_t *entry = sulist_container(lst, e, hash_entry_t);
         if( strcmp(entry->key, key) == 0 )
            return entry;
      }
      return NULL;
   }else{
      __ghash_get( table->subtables[index], key );
   }
}

#define ghash_remove(type) \
        (type)_ghash_remove
#define _ghash_remove(table, key) \
        __ghash_remove(table, key)
void *__ghash_remove(hashtbl_t *table, char *key){
   int index = table->hash(key, strlen(key), 
                           table->total_buckets, table->hash_factor);

   if( table->subtables[index] == NULL ){
      sulist_t *lst = table->buckets[index];
      sulist_foreach( lst, e ){
         hash_entry_t *entry = sulist_container(lst, e, hash_entry_t);
         if( strcmp(entry->key, key) == 0 ){
            sulist_rm_node( lst, entry );
            key_free(entry);
            return entry;
         }
      }
      return NULL;
   }else{
      __ghash_remove( table->subtables[index], key );
   }
}
   


//Generic entry for testing
typedef struct{
   hash_entry_t hash_entry;
   int item;
   char c;
}mytest_t;

mytest_t *make_entry(int val, char c, char *key){
   mytest_t *e = malloc(sizeof(mytest_t));
   e->item = val;
   e->c = c;
   assoc_key( &e->hash_entry, key );
   return e;
}

void main(){
   srand(time(NULL));

   hashtbl_t *new_table = ghash_create(10, mytest_t, hash_entry);
   ghash_insert( new_table, make_entry(99, 'A', "test"));
   mytest_t *removed = ghash_remove(mytest_t*)(new_table, "test");
   mytest_t *e = ghash_get(mytest_t*)(new_table, "test");
 
   if( e != NULL )
      printf("Got %d, %c\n", e->item, e->c);   
   else
      printf("NULL\n");

   printf("Removed: %d, %c\n", removed->item, removed->c);
}
