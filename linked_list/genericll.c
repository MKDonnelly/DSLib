#include "genericll.h"

list_t *__list_create(int ptr_offset){
   list_t *new_list = malloc(sizeof(list_t));
   new_list->head = NULL;
   new_list->len = 0;
   new_list->ptr_offset = ptr_offset;
   return new_list;
}

void __list_free(list_t **self, void (*free_element)(void*)){
   if( (*self)->len > 0 ){
      (*self)->len--;
      list_head_t *temp = (*self)->head->next;
      free_element( (*self)->head );
      (*self)->head = temp;
      __list_free(self, free_element);
   }else{
      free(*self);
      *self = NULL;
   }
}

#define POINTER_IN( element, ptr_offset )\
   (list_head_t*)( (char*)element + ptr_offset )

void __list_add(list_t *self, list_head_t **current, 
                void *new_element, int index){
   if( *current == NULL ){
      //Hit end of list. Put element there
      *current = POINTER_IN( new_element, self->ptr_offset );
      self->len++;
   }else if( index == 0 ){
      //Found the correct index. Place element by pushing it before head.
      list_head_t *temp = *current;
      *current = POINTER_IN( new_element, self->ptr_offset );
      (*current)->next = temp;
      self->len++;
   }else{
      __list_add(self, &((*current)->next), new_element, index - 1 );
   }
}

void *__list_get(list_t *self, list_head_t **current, int index ){
   if( *current == NULL ){
      return NULL;
   }else if( index == 0 ){
      return (void*)*current;
   }else{
      return __list_get(self, &((*current)->next), index - 1);
   }
}
