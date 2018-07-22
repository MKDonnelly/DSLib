#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Implements a min heap of elements
typedef struct{
   //An array of elements. This may be something like single
   //integers, or pointers.
   size_t **elements;
   int elements_len;
   int len;
   //Returns 1 if element1 < element2,
   // 0 else
   int (*compare)(size_t *element1, size_t *element2);
}heap_t;

heap_t *heap_create(int (*compare_function)(size_t*,size_t*), int start_size){
   heap_t *new_heap = malloc(sizeof(heap_t));
   new_heap->elements = malloc(sizeof(size_t*) * start_size);
   new_heap->elements_len = start_size;
   new_heap->len = 0;
   new_heap->compare = compare_function;
}

void bubble_up(heap_t *heap, int i){
   while( i / 2 > 0 ){
      if( heap->compare(heap->elements[i], heap->elements[i/2])){
         size_t *temp = heap->elements[i/2];
         heap->elements[i/2] = heap->elements[i];
         heap->elements[i] = temp;
      }
      i /= 2;
   }
}

int min_child(heap_t *heap, int i){
   if( (i * 2 + 1) > heap->len){
      return i * 2;
   }else{
      if( heap->compare(heap->elements[i*2], heap->elements[i*2+1]))
         return i * 2;
      else
         return i * 2 + 1;
   }
}

void bubble_down(heap_t *heap, int index){
   while( (index * 2) <= heap->len ){
      int mc = min_child(heap, index);
      if( heap->compare(heap->elements[mc], heap->elements[index])){
         size_t *tmp = heap->elements[index];
         heap->elements[index] = heap->elements[mc];
         heap->elements[mc] = tmp;
      }
      index = mc;
   }
}

size_t *grab_min(heap_t *heap){
   size_t *retval = heap->elements[1]; 
   heap->elements[1] = heap->elements[heap->len];
   heap->len--;
   bubble_down(heap, 1);
   return retval;
}

void heap_add(heap_t *heap, void *element){
   heap->len++;
   heap->elements[heap->len] = element;
   bubble_up(heap, heap->len);
}


typedef struct{
   int data;
}test_t;

int test_compare(size_t *element1, size_t *element2){
   if( ((test_t*)element1)->data < ((test_t*)element2)->data )
      return 1;
   return 0;
}

void main(){
   srand(time(NULL));
   heap_t *new_heap = heap_create(test_compare, 20);

   for(int i = 0; i < 9; i++){
      test_t *new_test = malloc(sizeof(test_t));
      new_test->data = i * 10;
      heap_add(new_heap, new_test);
   }

   for(int i = 0; i < 9; i++){
      test_t *ret = (test_t*)grab_min(new_heap);
      printf("%d\n", ret->data);
   }
}
