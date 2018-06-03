#pragma once

typedef struct dynarray{
   void *array;
   int element_size;
   int total_elements;
}dynarray_t;

void *dynarray_create( int start_size, int element_size );
void dynarray_add( dynarray_t *dynarray, void *element, int index );
void *dynarray_get_array( dynarray_t *dynarray ); 
