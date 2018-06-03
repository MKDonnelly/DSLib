#pragma once
#include "../linked_list/generic_ll.h"

#define push_queue( queue, item )\
        add_node_ll( queue, item, get_size_ll(queue))
#define pop_queue( queue )\
        rmi_node_ll( queue, 0 )
