#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Insertion sort, done iteratively
void insertion_sort( int *values, int size ){
   int partition_index = 1;
   for(int i = 0; i < size; i++){
      int sorted = partition_index;
      while( values[sorted] < values[sorted-1] ){
         int temp = values[sorted];
         values[sorted] = values[sorted-1];
         values[sorted-1] = temp;
         sorted--;
      }
      partition_index++;
   }
}

//Insertion sort, done recursively
void rec_insert_sort( int *values, int size ){
   if( size == 1 ){
      return;
   }
   rec_insert_sort( values, size-1 );

   while( size >= 2 && values[size-1] < values[size-2] ){
      int temp = values[size-1];
      values[size-1] = values[size-2];
      values[size-2] = temp;
      size--;
   }
}

void merge(int *dest, int *src1, int *src2, int srclen){
   int src1_len = srclen;
   int src2_len = srclen;
   int dest_len = 0;
   while( dest_len < (2 * srclen) ){
      if( src1_len > 0 && src2_len > 0 && src1[srclen-src1_len] <=
                                          src2[srclen-src2_len] ){
         dest[dest_len++] = src1[srclen-src1_len];
         src1_len--;
      }else if( src1_len > 0 && src2_len > 0 && src1[srclen-src1_len] > 
                                          src2[srclen-src2_len] ){
         dest[dest_len++] = src2[srclen-src2_len];
         src2_len--;
      }else if( src1_len <= 0 && src2_len > 0 ){
         dest[dest_len++] = src2[srclen-src2_len];
         src2_len--;
      }else if( src2_len <= 0 && src1_len > 0 ){
         dest[dest_len++] = src1[srclen-src1_len];
         src1_len--;
      }
   }  
}

void merge_sort( int *array, int length ){
   if( length == 1 ){
      return;
   }
   merge_sort( array, length / 2 );
   merge_sort( &array[length/2], length - (length / 2) );

   merge( array, 
}

void main(){

   int first[] = {1, 3, 5, 7};
   int second[] = {2, 4, 6, 8};
   int dest[8];
   merge(dest, first, second, 4);
   for(int i = 0; i < 8; i++)
      printf("%d ", dest[i]);
   printf("\n");

/*
   srand(time(NULL));

   int v[10];
   for(int i = 0; i < 10; i++)
      v[i] = rand() % 100;
   int v_len = 10;

   rec_insert_sort(v, v_len);

   for(int i = 0; i < v_len; i++)
      printf("%d ", v[i]);
   printf("\n");*/
}


