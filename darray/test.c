#include <stdio.h>
#include <stdlib.h>
#include "darray.h"

void main(){
   darray_t *d = darray_create(char *);

   darray_add(d, char*, "hello, there", 0);
   
   printf("%s\n", darray_get(d, char*, 0));

}
