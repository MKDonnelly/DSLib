#pragma once

#define DYNARRAY_TEMPLATE(type)					\
     struct dynarray_##type{					\
        type *array;						\
        int array_size; 					\
        int len;						\
	void (*add)(struct dynarray_##type *t, 			\
			type item, int index); 			\
	type (*get)(struct dynarray_##type *t,			\
			int index);				\
     };								\
								\
     void dynarray_add_##type (struct dynarray_##type *t, 	\
				type item, int index){		\
	if( t->array_size <= index){				\
	   t->array_size *= 2;					\
           t->array = realloc(t->array, 			\
                         t->array_size * sizeof(type));		\
	}							\
	t->array[index] = item;					\
	t->len++;						\
     }								\
     type dynarray_get_##type (struct dynarray_##type *t,	\
				int index){			\
	if( index < t->len )					\
	   return t->array[index];				\
     }								\
     struct dynarray_##type *dynarray_create_##type (){ 	\
        struct dynarray_##type *t = 				\
			malloc(sizeof(struct dynarray_##type)); \
        t->len = 0;						\
	t->array_size = 1;					\
	t->array = malloc(sizeof(type) * t->array_size);	\
        t->add = dynarray_add_##type ;				\
	t->get = dynarray_get_##type ;				\
     }							

#define DECLARE_DYNARRAY(name, type) \
     struct dynarray_##type *name = dynarray_create_##type (); 
