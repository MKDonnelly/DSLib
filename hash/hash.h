#pragma once

typedef struct{
   
}hashnode_t;

typedef struct{
   int total_elements;
   int hashtable_len;
   void **hash_array;
}hashtable_t;

void **make_hash_table(int buckets, int element_size);
int generic_hash(char *data, int max_val);
void insert_into_hash( hashtable_t *table, void *item);
void *get_from_hash( hashtable_t *table, void *key);
