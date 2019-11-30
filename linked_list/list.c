#include "list.h"

void list_add(list_t *l, void *element, int index){
   if( l->type == TYPE_SINGLE_INTRUSIVE )
      list_si_add(l->single_intrusive, element, index);
   else if( l->type == TYPE_SINGLE_VPTR )
      list_vptr_add(l->single_vptr, element, index);
}

void *list_rm_index(list_t *l, int index){
   if( l->type == TYPE_SINGLE_INTRUSIVE )
      return list_si_rm_index(l->single_intrusive, index);
   else if( l->type == TYPE_SINGLE_VPTR )
      return list_vptr_rm_index(l->single_vptr, index);
}

void list_rm_node(list_t *l, void *node){
   if( l->type == TYPE_SINGLE_INTRUSIVE )
      list_si_rm_node(l->single_intrusive, node);
   else if( l->type == TYPE_SINGLE_VPTR )
      list_vptr_rm_node(l->single_vptr, node);

}

void *list_get(list_t *l, int index){
   if( l->type == TYPE_SINGLE_INTRUSIVE )
      return list_si_get(l->single_intrusive, index);
   else if( l->type == TYPE_SINGLE_VPTR )
      return list_vptr_get(l->single_vptr, index);
}

int list_len(list_t *l){
   if( l->type == TYPE_SINGLE_INTRUSIVE )
      return list_si_len(l->single_intrusive);
   else if( l->type == TYPE_SINGLE_VPTR )
      return list_vptr_len(l->single_vptr);
}

int list_type(list_t *l){
   return l->type;
}

void list_free(list_t *l, void (*free_node)(void *node)){
   if( l->type == TYPE_SINGLE_INTRUSIVE )
      list_si_free(l->single_intrusive, free_node);
   else if( l->type == TYPE_SINGLE_VPTR )
      list_vptr_free(l->single_vptr, free_node);
}
