#include "list_vp.h"

list_vptr_t *list_vptr_create(){
   list_vptr_t *new_list = malloc(sizeof(list_vptr_t));
   new_list->head = NULL;
   new_list->elements = 0;
   return new_list;
}

void __list_vptr_free(list_vptr_node_t **list, void (*free_element)(void*)){
   if( (*list) == NULL ){
      return;
   }else{
      list_vptr_node_t **next = &(*list)->next;
      free_element( *list );
      __list_vptr_free(next, free_element);
   }
}

void __list_vptr_add(list_vptr_node_t **list, void *element, int index){
   if( *list == NULL ){
      list_vptr_node_t *new_node = malloc(sizeof(list_vptr_node_t));
      new_node->data = element;
      *list = new_node;
      return;
   }else if( index == 0 ){
      list_vptr_node_t *new_node = malloc(sizeof(list_vptr_node_t));
      new_node->data = element;
      new_node->next = (*list);
      (*list) = new_node;
      return;
   }else{
      __list_vptr_add( &(*list)->next, element, index-1 );
   }
}

void *__list_vptr_get(list_vptr_node_t **list, int index){
   if( (*list) == NULL ){
      return NULL;
   }else if( index == 0 ){
      return (*list)->data;
   }else{
      return __list_vptr_get( &(*list)->next, index-1 );
   }
}

void *__list_vptr_rm_index(list_vptr_node_t **list, int index){
   if( (*list) == NULL ){
      return NULL;
   }else if( index == 0 ){
      list_vptr_node_t *temp = (*list);
      (*list) = (*list)->next;
      void *t = temp->data;
      free(temp);
      return t;
   }else{
      return __list_vptr_rm_index( &(*list)->next, index-1 );
   } 
}

void __list_vptr_rm_node(list_vptr_node_t **list, void *node){
   if( (*list) == NULL ){
      return;
   }else if( (*list)->data == node ){
      list_vptr_node_t *temp = (*list);
      (*list)->next = (*list)->next->next;
      free(temp);
   }else{
      __list_vptr_rm_node( &(*list)->next, node );
   }
}
