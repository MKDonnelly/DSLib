#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dynarray{
   void *array;
   int array_size;   //Size of the array, in bytes
   int element_size;
}dynarray_t;

#define INIT_DYNARRAY( initial_size, type ) \
     { NULL, initial_size, sizeof(type) }

dynarray_t *dynarray_create(int start_size, int type_size){
   dynarray_t *new_dynarray = malloc(sizeof(dynarray_t));
   new_dynarray->size = start_size;
   new_dynarray->array = malloc(type_size * start_size);
   return new_dynarray;
}

void dynarray_add(dynarray_t *dynarray, int new_item, int index){
   if( dynarray->size <= index ){
      dynarray->size *= 2;
      dynarray->array = realloc(dynarray->array, dynarray->size * sizeof(int) );
   }
   dynarray->array[index] = new_item;
}

int *dynarray_get_array(dynarray_t *dynarray){
   return dynarray->array;
}

void main(){

   dynarray_t *a = dynarray_create(1);

   for(int i = 0; i < 10; i++)
      dynarray_add(a, i, i);

   int *b = dynarray_get_array(a);
  
   for(int i = 0; i < 10; i++)
      printf("%d\n", b[i]);
}

