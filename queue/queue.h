#pragma once
#include "../linked_list/list.h"

typedef list_t queue_t;

#define create_queue(struct_type, struct_member) \
        slist_create(struct_type, struct_member)

#define enqueue_queue(queue, item)\
        slist_append(queue, item)

#define dequeue_queue(queue) \
        slist_rm_index(queue, 0)

#define len_queue(queue) \
        slist_len(queue)
