#include "sulist.h"

sulist_t *__sulist_create(int ptr_offset){
   sulist_t *new_list = malloc(sizeof(sulist_t));
   new_list->head = NULL;
   new_list->len = 0;
   new_list->ptr_offset = ptr_offset;
   return new_list;
}

void __sulist_free(sulist_t **self, void (*free_element)(void*)){
   if( (*self)->len > 0 ){
      (*self)->len--;
      sulist_head_t *temp = (*self)->head->next;
      free_element( (*self)->head );
      (*self)->head = temp;
      __sulist_free(self, free_element);
   }else{
      free(*self);
      *self = NULL;
   }
}

void __sulist_add(sulist_t *self, sulist_head_t **current, 
                  void *new_element, int index){
   if( *current == NULL ){
      //Hit end of list. Put element there
      *current = sulist_ptrin( self, new_element );
      (*current)->next = NULL;
      self->len++;
   }else if( index == 0 ){
      //Found the correct index. Place element by pushing it before head.
      sulist_head_t *temp = *current;
      *current = sulist_ptrin( self, new_element );
      (*current)->next = temp;
      self->len++;
   }else{
      __sulist_add(self, &((*current)->next), new_element, index - 1 );
   }
}

void *__sulist_rm_index(sulist_t *self, sulist_head_t **current, 
                        int index){
   if( *current == NULL ){
      //Hit end of list without finding index
      return NULL;
   }else if( index == 0 ){
      sulist_head_t *temp = *current;
      (*current) = (*current)->next;
      self->len--;
      return temp;
   }else{
      __sulist_rm_index(self, &((*current)->next), index-1);
   }
}

void __sulist_rm_node(sulist_t *self, sulist_head_t **current, 
                      sulist_head_t *node){
   if( *current == NULL ){
      return;
   }else if( *current == node ){
      (*current) = (*current)->next;
      self->len--;
   }else{
      __sulist_rm_node(self, &((*current)->next), node);
   }
}


void *__sulist_get(sulist_t *self, sulist_head_t **current, int index ){
   if( *current == NULL ){
      return NULL;
   }else if( index == 0 ){
      return (void*)*current;
   }else{
      return __sulist_get(self, &((*current)->next), index - 1);
   }
}
