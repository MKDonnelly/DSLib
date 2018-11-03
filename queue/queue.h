#pragma once
#include "../linked_list/single/slist.h"

typedef slist_t queue_t;
typedef slist_head_t queue_element_t;

#define create_queue(struct_type, struct_member) \
        slist_create(struct_type, struct_member)

#define enqueue_queue(queue, item)\
        slist_append(queue, item)

#define dequeue_queue(queue) \
        slist_rm_index(queue, 0)

#define len_queue(queue) \
        slist_len(queue)
