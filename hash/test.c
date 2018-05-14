#include <stdio.h>
#include <stdlib.h>

void main(){
   FILE *input = fopen("test.txt", "r");
   char buf[200];
   int val;
   fscanf(input, "%s %d\n", buf, &val);

   printf("%s: %d\n", buf, val);
   fscanf(input, "%s %d\n", buf, &val);
   printf("%s: %d\n", buf, val);
}
