#include "genericll.h"

void __list_add(list_t *list, list_head_t **head, void *item, int pos){

   if( *head == NULL ){
      list->total_elements++;
      *head = (list_head_t*)((char*)item + list->offset_of_ptr);
   }else if( pos == 0 ){
      list->total_elements++;
      list_head_t *temp = *head;
      *head = (list_head_t*)((char*)item + list->offset_of_ptr);
      (*head)->next = temp;
   }else{
      __list_add( list, &((*head)->next), item, pos - 1);
   }
}

void *__list_removeby_index(list_t *list, list_head_t **head, int pos){
   if( *head == NULL ){
      return NULL;
   }else if(pos == 0){
      list_head_t *ret = *head;
      *head = (*head)->next;
      return (char*)ret - list->offset_of_ptr;
   }else{
      __list_removeby_index(list, &((*head)->next), pos-1);
   }
}


void *__list_getby_index( list_t *list, list_head_t **head, int pos){
   if( *head == NULL ){
      return NULL;
   }else if( pos == 0 ){
      return (char*)*head - list->offset_of_ptr;
   }else{
      __list_getby_index( list, &((*head)->next), pos - 1);
   }
}

