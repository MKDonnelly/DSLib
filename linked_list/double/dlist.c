#include "genericll.h"

//Create a new empty list
dlist_t *__dlist_create(int ptr_offset){
   list_t *new_list = malloc(sizeof(list_t));
   new_list->head = NULL;
   new_list->len = 0;
   new_list->ptr_offset = ptr_offset;
   return new_list;
}

void __dlist_free(dlist_t **self, void (*free_element)(void*)){

}

void __dlist_add(dlist_t *list, dlist_head_t **current, 
                 void *item, int index){
   if( *current == NULL ){
      //Hit the end of the list. Place the item
      *current = dlist_member( list, item );
      (*current)->next = NULL;
      list->len++;
   }else if( 
}

list_head_t *__dlist_get(dlist_t *list, int index){

}

void *__dlist_rm_index(dlist_t *list, dlist_head_t **current, int index){

}

void __dlist_rm_node(dlist_t *list, dlist_head_t **current, 
                     dlist_head_t *node){

}

