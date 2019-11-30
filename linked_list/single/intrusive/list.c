#include "list.h"
#include <stdlib.h>

list_t *list_create(void *(*node_get_next)(void *node_obj),
                    void (*node_set_next)(void *node_obj, void *new_next)){
   list_t *l = malloc(sizeof(list_t));
   l->head = NULL;
   l->node_get_next = node_get_next;
   l->node_set_next = node_set_next;
   l->len = 0;
   return l;
}

void __list_add(list_t *l, void **current, void *item, int index){
   if( *current == NULL ){
      *current = item;
      l->node_set_next(item, NULL);
      l->len++;
   }else if( index == 0 ){
      void *temp = *current;

      *current = item;
      l->node_set_next(item, temp);
      l->len++;
   }else{
      __list_add(l, l->node_get_next(*current), item, index-1);
   }
}


void *__list_get(list_t *l, void **current, int index){
   if( *current == NULL || index == 0 ){
      return *current;
   }else{
      return __list_get(l, l->node_get_next(*current), index-1);
   } 
}


void *__list_rmi(list_t *l, void **current, int index){
   if( *current == NULL ){
      return NULL;
   }else if( index == 0 ){
      void *temp = (*current);
      (*current) = l->node_get_next(temp);
      l->len--;
      return temp;
   }else{
      return __list_rmi(l, l->node_get_next(*current), index-1);
   }
}

void __list_rmn(list_t *l, void **current, void *node){
   if( *current == NULL ){
      return;
   }else if( *current == node ){
      void *temp = l->node_get_next(*current);
      *current = temp;
   }else{
      __list_rmn(l, l->node_get_next(*current), node);
   }
}


void __list_free(list_t *l, void **current, void (*free_element)(void*)){
   if( *current == NULL ){
      free(l);
   }else{
      void *temp = l->node_get_next(*current);
      free_element(*current);
      __list_free(l, &temp, free_element);
   }
}
