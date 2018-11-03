#pragma once

typedef struct darray{
   int len;
   int elem_size;
   int allocsize;
   void *elements;
}darray_t;

#define darray_len(darray) (darray)->len

#define darray_create(element_type) \
        __darray_create(sizeof(element_type))
darray_t *__darray_create(int elem_size);

#define darray_append(darray, type, element) \
        darray_add(darray, type, element, (darray)->len)

#define darray_add(darray, type, element, index) \
        do{					\
           if(((index+1) * (darray)->elem_size ) > (darray)->allocsize){\
              (darray)->allocsize *= 2; 				\
              (darray)->elements = realloc((darray)->elements, 		\
                              (darray)->allocsize * (darray)->elem_size); \
           }								\
           ((type*)(darray)->elements)[index] = element;		\
           (darray)->len++; 						\
        }while(0); 

#define darray_rm(darray, type, index) \
     ((type*)(darray)->elements)[index] = ((type*)(darray)->elements)[(darray)->len]; 	\
     (darray)->len--;        

#define darray_get(darray, type, index) \
        ((type*)(darray)->elements)[index]
