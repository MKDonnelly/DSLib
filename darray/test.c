#include <stdio.h>
#include <stdlib.h>
#include "darray.h"

typedef struct mytest{
   int a, b, c;
   float d;
}mytest_t;

void main(){
   darray_t *d = darray_create(struct mytest);

   struct mytest t;
   t.a = t.b = t.c = 999;
   t.d = 1.234;   

   darray_add(d, struct mytest, t, 1);
   
   struct mytest gotten = darray_get(d, struct mytest, 1);
   printf("%d, %d, %d, %f\n", gotten.a, gotten.b, gotten.c, gotten.d);

}
