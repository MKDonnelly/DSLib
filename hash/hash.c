#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../linked_list/generic_ll/generic_ll.h"

typedef struct node{
   struct node *next;
   char filename[200];
   int filesize;
}my_node;

my_node *create_node(char *filename, int size){
   my_node *new_node = malloc(sizeof(my_node));
   strcpy(new_node->filename, filename);
   new_node->filesize = size;
   return new_node;
}
//////////

//Makes a hash table given its size.
my_node **make_hash_table(int size){
   return malloc( sizeof(my_node*) * size );
}

//used to hash a string. returns value from 0..max_value
int hash_string( char *string, int max_value ){
   int accumulator = 0;
   int string_length = strlen(string);
   for(int i = 0; i < string_length; i++){
      accumulator += (char)string[i] * i;
      accumulator %= max_value;
   }
   return (accumulator % max_value);
}


void insert_into_hash( my_node *node, my_node *node_array[], int max ){
   int hash = hash_string( node->filename, max );
   add_node_ll( node_array[hash], node, 0 );
}

my_node *get_from_hash( char *str, my_node *node_array[], int max ){
   int hash = hash_string( str, max );
   foreach_in_gll( node_array[hash], entry ){
      if( strcmp(entry->filename, str) == 0 )
         return entry;
   }
   return NULL;
}


int main(){
   const int HASH_SIZE = 10000;
   my_node **hash_array = make_hash_table(HASH_SIZE);

//Read in data from file
   char buf[2000];
   int length;
   FILE *files = fopen("files.txt", "r");
   
   char read_stat = fscanf(files, "%s %d\n", buf, &length);

   while( read_stat != EOF ){
      my_node *new_node = create_node( buf, length );
      insert_into_hash( new_node, hash_array, HASH_SIZE );

      read_stat = fscanf(files, "%s %d\n", buf, &length);
   }

   fclose(files);  

   char buf2[2000];
   int length2;
   FILE *files2 = fopen("files.txt", "r");
   
   char read_stat2 = fscanf(files2, "%s %d\n", buf2, &length2);

   clock_t begin = clock();      
   while( read_stat2 != EOF ){

      my_node *n = get_from_hash( buf2, hash_array, HASH_SIZE);
      read_stat2 = fscanf(files2, "%s %d\n", buf2, &length2);
   }
   clock_t end = clock();
   double time_elapsed = (double)(end - begin) / CLOCKS_PER_SEC;

   printf("Time elapsed: %f\n", time_elapsed);

   fclose(files2);  
/*
   while(1){
      char user_input[200];
      printf("Query> ");
      fscanf(stdin, "%s", user_input);

      clock_t begin = clock();      
      my_node *n = get_from_hash( user_input, hash_array, HASH_SIZE);
      clock_t end = clock();
      double time_elapsed = (double)(end - begin) / CLOCKS_PER_SEC;
      if( n != NULL )
         printf("%s: %d\n", n->filename, n->filesize);
      else
         printf("NOT FOUND!\n");
      printf("Query took %lfs\n", time_elapsed);
   }*/
}
