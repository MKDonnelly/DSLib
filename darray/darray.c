#include "darray.h"
#include <stdlib.h>

darray_t *__darray_create(int elem_size){
   darray_t *darray = malloc(sizeof(darray_t));
   darray->len = 0;
   darray->elem_size = elem_size;
   darray->allocsize = elem_size;
   darray->elements = malloc(elem_size * 1);
   return darray;
}

