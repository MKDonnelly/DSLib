#pragma once
#include "../linked_list/generic_ll.h"

#define push_stack( stack, element ) \
        list_add( stack, element, 0 )

#define pop_stack( stack ) \
        list_rm_index( stack, 0 )
