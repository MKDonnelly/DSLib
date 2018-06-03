#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
   srand(time(NULL));

   clock_t begin = clock();
   for(int i = 0; i < 1000000; i++){
      char *mem = malloc(rand() % 10000);
      free(mem);
   }
   clock_t end = clock();

   printf("Elapsed time: %lf\n", (double)(end - begin) / CLOCKS_PER_SEC);

   return 0;
}

