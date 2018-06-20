#pragma once
#include "../linked_list/genericll.h"

#define stack_push( stack, element ) \
        list_add( stack, element, 0 )

#define stack_pop( stack ) \
        list_rm_index( stack, 0 )

#define stack_peek( stack ) \
        list_getby_index( stack, 0 )

#define stack_size( stack )\
        list_size( stack )

#define INIT_STACK( stack, type, member ) INIT_LIST( stack, type, member )
