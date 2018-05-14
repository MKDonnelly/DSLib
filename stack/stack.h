#pragma once
#include "../linked_list/abstract_ll/abstract_ll.h"

#define push_stack( stack, element ) \
        __add_node_ll( (void**)&stack, element, 0 )

#define pop_stack( stack ) \
       __rm_node_ll( (void**)&stack, 0 )
