#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Implements a min heap of elements
typedef struct{
   //Dynamic array of elements being held
   size_t **elements;
   
   //The length of the elements array
   int elements_len;

   //The number of items in elements.
   //Note: elements_len != total_items
   int total_items;

   //Returns 1 if element1 should go before element2.
   //Returns 0 if element2 should go before element1.
   //Basically, is the subset [element1, element2] correctly
   //ordered?  Different comparison functions give min/max heaps.
   int (*compare)(size_t *element1, size_t *element2);
}heap_t;


heap_t *heap_create(int (*compare_function)(size_t*,size_t*)){
   heap_t *new_heap = malloc(sizeof(heap_t));
   new_heap->total_items = 0;
   new_heap->elements_len = 1;
   new_heap->elements = malloc(sizeof(size_t*) * new_heap->elements_len);
   new_heap->compare = compare_function;
}

void heap_free(heap_t *h){
   free(h->elements);
   free(h);
   h = NULL;
}

//Given an index within a heap, continually move the
//element at that index up the heap until it rests in
//its final position.
static void bubble_up(heap_t *heap, int i){
   while( i / 2 > 0 ){
      if( heap->compare(heap->elements[i], heap->elements[i/2])){
         size_t *temp = heap->elements[i/2];
         heap->elements[i/2] = heap->elements[i];
         heap->elements[i] = temp;
      }
      i /= 2;
   }
}

static int next_child(heap_t *heap, int i){
   if( (i * 2 + 1) > heap->total_items){
      return i * 2;
   }else{
      if( heap->compare(heap->elements[i*2], heap->elements[i*2+1]))
         return i * 2;
      else
         return i * 2 + 1;
   }
}


static void bubble_down(heap_t *heap, int index){
   while( (index * 2) <= heap->total_items ){
      //Even if we use a max-heap comparison function, this
      //still works. Why?
      int child = next_child(heap, index);
      if( heap->compare(heap->elements[child], heap->elements[index])){
         size_t *tmp = heap->elements[index];
         heap->elements[index] = heap->elements[child];
         heap->elements[child] = tmp;
      }
      index = child;
   }
}

//Removes and returned minimum element for a min heap.
//For a max heap, does the same, but for the max element.
size_t *rm_top(heap_t *heap){
   size_t *retval = heap->elements[1];
   heap->elements[1] = heap->elements[heap->total_items];
   heap->total_items--;
   bubble_down(heap, 1);
   return retval;
}

//Returns the value of the top element (smallest in min
//heap, largest in max heap). Does not remove top element.
size_t *get_top(heap_t *heap){
   return heap->elements[1];
}

int heap_empty(heap_t *heap){
   return heap->total_items > 0 ? 0 : 1;
}

void heap_add(heap_t *heap, void *element){
   heap->total_items++;

   //Resize needed
   if( heap->total_items >= heap->elements_len ){
      //Scale allocated space by a factor of 2.
      //The array will grow like 1 2 4 8 16 32 64...
      heap->elements_len *= 2;
      heap->elements = realloc(heap->elements, 
                               heap->elements_len * sizeof(size_t*));
   }

   //Insert elements and bubble it up
   heap->elements[heap->total_items] = element;
   bubble_up(heap, heap->total_items);
}
