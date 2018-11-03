#pragma once

#include "../linked_list/single/slist.h"

//TODO instead of a string key, have a generic key that
//     can refer to any series of bytes.
typedef struct{
   slist_head_t list_member;
   char *key;
}hash_entry_t;

struct htable;
typedef struct{
   //TODO use pointer tagging for type
   char type; //0 for list, 1 for htable
   union{
      slist_t *list;
      struct htable *table;
   };
}bucket_t;

//A table representing a generic hash.
typedef struct htable{
   //We convert a linked list of values into
   //a sub-hashtable if the list exceeds max_load,
   //and we convert a hash table into a linked list
   //if the size shrinks below min_load
   int max_load, min_load;

   //This is an intrusive hash table; structures
   //must have a hash_enty_t within them for this
   //hash algorithm to use. This is the offset of that
   //entry within the type of structure to manage.
   int entry_offset;

   //The number of items in this table
   int total_items;

   //Number of buckets to use for a hash table.
   //This is fixed, and is inherited by sub-hashtables.
   int total_buckets;

   bucket_t *buckets;
   //hash_factor appends an extra character onto the key we
   //are using. When we expand a list, all of the elements will
   //hash to the same value. To prevent that, this is used.
   int hash_factor;
   int (*hash)(void *object, int obj_len, int max, int factor);
}htable_t;

#define hash_member(element, htable) \
        (hash_entry_t*)((char*)element + (htable)->entry_offset)
#define assoc_key(htable, element, key) \
        __assoc_key(hash_member(element, htable), key)

void __assoc_key(hash_entry_t *entry, const char *key);

//Creates a generic hash table. By setting maxload to INT_MAX and
//minload to 0, this behaves as a normal hash table.
#define ghash_create(size, maxload, minload, struct_type, struct_entry) \
        __ghash_create( size, maxload, minload, \
                        __builtin_offsetof(struct_type,struct_entry))
htable_t *__ghash_create(int buckets_per_level, int maxload,
                         int minload, int hashentry_offset);

//Inserts an element into the hash
void ghash_insert(htable_t *table, void *new_element);

//Given a key, retrieves the corresponding data from the hash.
//Returns NULL if the key is not found. Example call:
//my_structure_t *structure = ghash_get(my_structure_t*)(my_table, "key");
#define ghash_get( type ) \
   (type) _ghash_get
#define _ghash_get(table, key) \
   ((char*)__ghash_get(table, key) - (table)->entry_offset)
void *__ghash_get(htable_t *table, char *key);

//Given a key, removes and returns the corresponding data from the htable.
//Does nothing and returns NULL if the key is not present. Example call:
//my_structure_t *structure = ghash_remove(my_structure_t*)(my_table, "key");
#define ghash_remove(type) \
        (type)__ghash_remove
void *__ghash_remove(htable_t *table, char *key);
