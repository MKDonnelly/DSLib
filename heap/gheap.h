#pragma once

typedef struct heap heap_t;

heap_t *heap_create(int (*compare_function)(size_t *e1, size_t *e2));
void heap_free(heap_t *heap);
size_t *rm_top(heap_t *heap);
size_t *get_top(heap_t *heap);
void heap_add(heap_t *heap, void *element);
int heap_empty(heap_t *heap);

