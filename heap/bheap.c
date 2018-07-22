#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
   int *elements;
   int len;
}heap_t;

void bubble_up(heap_t *heap, int i){
   while( i / 2 > 0 ){
      if( heap->elements[i] < heap->elements[i/2]){
         int temp = heap->elements[i/2];
         heap->elements[i/2] = heap->elements[i];
         heap->elements[i] = temp;
      }
      i /= 2;
   }
}

int min_child(heap_t *heap, int i){
   if( i * 2 + 1 > heap->len){
      return i * 2;
   }else{
      if( heap->elements[i*2] < heap->elements[i*2+1])
         return i * 2;
      else
         return i * 2 + 1;
   }
}

void bubble_down(heap_t *heap, int index){
   while( (index * 2) <= heap->len ){
      int mc = min_child(heap, index);
      if( heap->elements[index] > heap->elements[mc] ){
         int tmp = heap->elements[index];
         heap->elements[index] = heap->elements[mc];
         heap->elements[mc] = tmp;
      }
      index = mc;
   }
}

int grab_min(heap_t *heap){
   int retval = heap->elements[1]; 
   heap->elements[1] = heap->elements[heap->len];
   heap->len--;
   bubble_down(heap, 1);
   return retval;
}

void heap_add(heap_t *heap, int element){
   heap->len++;
   heap->elements[heap->len] = element;
   bubble_up(heap, heap->len);
}

void main(){
   srand(time(NULL));
   heap_t new_heap;
   new_heap.elements = malloc(sizeof(int) * 20);
   new_heap.elements[0] = 0;
   new_heap.len = 0;

   for(int i = 0; i < 9; i++) 
      heap_add(&new_heap, rand() % 100);

   for(int i = 0; i < 9; i++)
      printf("%d\n", grab_min(&new_heap));
}
