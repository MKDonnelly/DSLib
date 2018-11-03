#include "slist.h"

slist_t *__slist_create(int ptr_offset){
   slist_t *new_list = malloc(sizeof(slist_t));
   new_list->head = NULL;
   new_list->len = 0;
   new_list->ptr_offset = ptr_offset;
   return new_list;
}

void __slist_free(slist_t **self, void (*free_element)(void*)){
   if( (*self)->len > 0 ){
      (*self)->len--;
      slist_head_t *temp = (*self)->head->next;
      free_element( (*self)->head );
      (*self)->head = temp;
      __slist_free(self, free_element);
   }else{
      free(*self);
      *self = NULL;
   }
}

void __slist_add(slist_t *self, slist_head_t **current, 
                  void *new_element, int index){
   if( *current == NULL ){
      //Hit end of list. Put element there
      *current = slist_member( self, new_element );
      (*current)->next = NULL;
      self->len++;
   }else if( index == 0 ){
      //Found the correct index. Place element by pushing it before head.
      slist_head_t *temp = *current;
      *current = slist_member( self, new_element );
      (*current)->next = temp;
      self->len++;
   }else{
      __slist_add(self, &((*current)->next), new_element, index - 1 );
   }
}

void *__slist_rm_index(slist_t *self, slist_head_t **current, 
                        int index){
   if( *current == NULL ){
      //Hit end of list without finding index
      return NULL;
   }else if( index == 0 ){
      slist_head_t *temp = *current;
      (*current) = (*current)->next;
      self->len--;
      return temp;
   }else{
      __slist_rm_index(self, &((*current)->next), index-1);
   }
}

void __slist_rm_node(slist_t *self, slist_head_t **current, 
                      slist_head_t *node){
   if( *current == NULL ){
      return;
   }else if( *current == node ){
      (*current) = (*current)->next;
      self->len--;
   }else{
      __slist_rm_node(self, &((*current)->next), node);
   }
}


void *__slist_get(slist_t *self, slist_head_t **current, int index ){
   if( *current == NULL ){
      return NULL;
   }else if( index == 0 ){
      return (void*)*current;
   }else{
      return __slist_get(self, &((*current)->next), index - 1);
   }
}
