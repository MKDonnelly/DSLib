#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "darray.h"

DARRAY_TEMPLATE_HEADER(int)
DARRAY_TEMPLATE_BODY(int)

void main(){

   darray_type(int) *a = darray_create(int)();

   for(int i = 0; i < 10; i++){
      darray_append(int)(a, i);
   }

   for(int i = 0; i < 10; i++){
      printf("%d\n", darray_get(int)(a, i));
   }
}
