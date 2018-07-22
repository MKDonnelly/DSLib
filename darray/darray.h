#pragma once

#define DARRAY_TEMPLATE_HEADER(type)				\
     struct darray_##type{					\
        type *array;						\
        int array_size; 					\
        int len;						\
     };								\

#define darray_add(type) darray_add_##type
#define darray_append(type) darray_append_##type
#define darray_get(type) darray_get_##type
#define darray_create(type) darray_create_##type
#define darray_rm(type) darray_rm_##type
#define darray_type(type) struct darray_##type
#define darray_typeof(darray) typeof( (darray)->array )
#define darray_len(darray) (darray)->len

#define DARRAY_TEMPLATE_BODY(type)				\
     void darray_add_##type (struct darray_##type *t, 		\
				type item, int index){		\
	if( t->array_size <= index){				\
	   t->array_size *= 2;					\
           t->array = realloc(t->array, 			\
                         t->array_size * sizeof(type));		\
	}							\
	t->array[index] = item;					\
	t->len++;						\
     }								\
     void darray_append_##type (struct darray_##type *t,	\
				type item){			\
	darray_add_##type (t, item, t->len );			\
     }								\
     type darray_get_##type (struct darray_##type *t,		\
				int index){			\
	if( index < t->len )					\
	   return t->array[index];				\
     }								\
     void darray_rm_##type (struct darray_##type *t,		\
				int index){			\
        t->array[index] = t->array[t->len];			\
	t->len--;						\
     }								\
     type *darray_content_##type (struct darray_##type *t){	\
	return t->array;					\
     }								\
     struct darray_##type *darray_create_##type (){ 		\
        struct darray_##type *t = 				\
			malloc(sizeof(struct darray_##type)); 	\
        t->len = 0;						\
	t->array_size = 1;					\
	t->array = malloc(sizeof(type) * t->array_size);	\
     }							
