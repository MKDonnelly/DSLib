#include "list.h"

list_t *list_create(){
   list_t *new_list = malloc(sizeof(list_t));
   new_list->head = NULL;
   new_list->elements = 0;
   return new_list;
}

void __list_free(node_t **list, void (*free_element)(void*)){
   if( (*list) == NULL ){
      return;
   }else{
      node_t **next = &(*list)->next;
      free_element( *list );
      __list_free(next, free_element);
   }
}
/*   if( index == 0 || *list == NULL ){
      node_t *new_node = malloc(sizeof(node_t));
      new_node->data = element;

      if( *list == NULL ){
         *list = new_node;
      }else{
         new_node->next = (*list)->next;
      }
      return;*/

void __list_add(node_t **list, void *element, int index){
   if( *list == NULL ){
      node_t *new_node = malloc(sizeof(node_t));
      new_node->data = element;
      *list = new_node;
      return;
   }else if( index == 0 ){
      node_t *new_node = malloc(sizeof(node_t));
      new_node->data = element;
      new_node->next = (*list);
      (*list) = new_node;
      return;
   }else{
      __list_add( &(*list)->next, element, index-1 );
   }
}

void *__list_get(node_t **list, int index){
   if( (*list) == NULL ){
      return NULL;
   }else if( index == 0 ){
      return (*list)->data;
   }else{
      return __list_get( &(*list)->next, index-1 );
   }
}

void *__list_rm_index(node_t **list, int index){
   if( (*list) == NULL ){
      return NULL;
   }else if( index == 0 ){
      node_t *temp = (*list);
      (*list) = (*list)->next;
      void *t = temp->data;
      free(temp);
      return t;
   }else{
      return __list_rm_index( &(*list)->next, index-1 );
   } 
}
