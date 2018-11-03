#pragma once
#include "../linked_list/isingle/slist.h"

typedef slist_t stack_t;

#define stack_push(stack, element) \
        slist_add(stack, element, 0)

#define stack_pop(stack) \
        slist_rm_index(stack, 0)

#define stack_peek(stack) \
        slist_get(stack, 0)

#define stack_size(stack)\
        slist_len(stack)

#define create_stack(struct_type, struct_member) \
        slist_create(struct_type, struct_member)
