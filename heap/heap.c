#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct heap{
   int *elements;
   int total_elements;
}heap_t;


void bubble_up( heap_t *heap, int index ){
   if( heap->elements[index / 2] < heap->elements[index] ){
      return;
   }else{
      int temp = heap->elements[index];
      heap->elements[index] = heap->elements[index / 2];
      heap->elements[index / 2] = temp;
      bubble_up( heap, index / 2 );
   }
}

void minheap_insert( heap_t *heap, int element ){
   heap->total_elements++;
   heap->elements[heap->total_elements] = element;
   if( heap->total_elements != 1 )
      bubble_up( heap, heap->total_elements );
}

void bubble_down( heap_t *heap, int index ){

   //Find the minimum child
/*
   if( index*2 < heap->total_elements && heap->elements[index] < heap->elements[index*2] && heap->elements[index] < heap->elements[index*2+1]){
      return;
   }else{
      int temp = heap->elements[index];
      heap->elements[index] = heap->elements[index*2];
      heap->elements[index*2] = temp;
      bubble_down( heap, index * 2);
   }*/
}

int minheap_getsmallest( heap_t *heap ){
   int smallest = heap->elements[1];

   //replace the element removed with the last
   //element and have it bubble down.
   heap->elements[1] = heap->elements[heap->total_elements];
   heap->total_elements--;
   bubble_down( heap, 1 );

   return smallest;
}

int main(){
   srand(time(NULL));
   heap_t *h = malloc(sizeof(heap_t));
   h->elements = malloc(sizeof(int) * 20);
   h->total_elements = 0;

   printf("HeapSort Test...\n");
   for(int i = 0; i < 10; i++){
      int r = rand() % 100;
      printf("%d, ", r);
      minheap_insert( h, r );
   }
   printf("\n");

   printf("Now in sorted order...\n");
   for(int i = 0; i < 10; i++){
      printf("%d, ", minheap_getsmallest(h));
   }
   printf("\n");

   return 0;
}


