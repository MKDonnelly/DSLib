#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynarray.h"

DYNARRAY_TEMPLATE(int)

void main(){
   DECLARE_DYNARRAY(new_dynarray, int);

   for(int i = 0; i < 10; i++){
      new_dynarray->add(new_dynarray, i, i);
   }

   for(int i = 0; i < 10; i++){
      printf("Got %d\n", new_dynarray->get(new_dynarray, i));
   }
}
