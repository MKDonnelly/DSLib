#include <stdio.h>
#include <stdlib.h>

int main(){
   FILE *input = fopen("data.txt", "r");

   int data_points[1000] = {0};

   int data;
   char stat = fscanf(input, "%d", &data);
   while(stat != EOF){
      if( data < 1000 )
         data_points[data]++;
      stat = fscanf(input, "%d", &data);
   }

   for(int i = 0; i < 1000; i++){
      if( data_points[i] != 0 ){
         printf("[value:%d]:", i);
         for(int j = 0; j < data_points[i]; j++)
            printf("|");
         printf("\n");
     }
   }

   return 0;
}
