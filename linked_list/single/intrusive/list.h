#pragma once

//Generic list type
typedef struct list{
   //This will hold a chain of user-defined
   //structures. The structure will have within
   //it a pointer to a structure of the same type
   //(the next pointer for the linked list)
   void *head;

   //This generic linked list implementation has no
   //idea what type of data it is being passed. In
   //order to function correctly, we only need to 
   //have a setter and getter (defined by the library user)
   //to modify the next field within the structure 
   void *(*node_get_next)(void *node_obj);
   void (*node_set_next)(void *node_obj, void *new_next);

   //Number of elements in the list
   int len;
}list_t;

#define list_len(l) (l)->len

list_t *list_create(void *(*node_get_next)(void *node_obj),
                    void (*node_set_next)(void *node_obj, void *new_next));

#define list_add(list, item, index) \
        __list_add(list, &(list)->head, item, index)
void __list_add(list_t *l, void **current, void *item, int index);

#define list_get(list, index) \
        __list_get(list, &(list)->head, index)
void *__list_get(list_t *l, void **current, int index);

#define list_rmi(list, index) \
        __list_rmi(list, &(list)->head, index)
void *__list_rmi(list_t *l, void **current, int index);

#define list_rmn(list, node) \
        __list_rmn(list, &(list)->head, node)
void __list_rmn(list_t *l, void **current, void *node);

#define list_free(list, free_func) \
        __list_free(list, &(list)->head, free_func)
void __list_free(list_t *l, void **current, void (*free_element)(void*));
