#pragma once
#include "../linked_list/single/list.h"

typedef struct{
   char *name;
   list_t *edges;
}vertex_t;

vertex_t *vertex_create(const char *name);
int vertex_has_edge(vertex_t *v, const char *going_to);

typedef struct{
   //Holds a list of vertex_t's
   list_t *vertexes;
}graph_t;

graph_t *graph_create();
void graph_add_vertex(graph_t *g, vertex_t *v);
vertex_t *graph_find_vertex(graph_t *g, const char *name);
void graph_connect_vertexes(graph_t *g, const char *from, const char *to);
