#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

vertex_t *vertex_create(const char *name){
   vertex_t *new_vertex = malloc(sizeof(vertex_t));
   new_vertex->name = strdup(name);
   new_vertex->edges = list_create();
   return new_vertex;
}

int vertex_has_edge(vertex_t *v, const char *edge){
   list_iter(v->edges, iter){
      if( strcmp(edge, (char*)iter->data) == 0 )
         return 1;
   }
   return 0;
}


graph_t *graph_create(){
   graph_t *g = malloc(sizeof(graph_t));
   g->vertexes = list_create();
   return g;
}

void graph_add_vertex(graph_t *g, vertex_t *v){
   list_add(g->vertexes, v, 0);
}

vertex_t *graph_find_vertex(graph_t *g, const char *name){
   list_iter(g->vertexes, vertex_iter){
      if( strcmp(((vertex_t*)vertex_iter->data)->name, name) == 0 )
         return (vertex_t*)vertex_iter->data;
   }
   return NULL;
}


void graph_connect_vertexes(graph_t *g, const char *from, const char *to){
   vertex_t *from_vertex = graph_find_vertex(g, from);
   if( from_vertex != NULL ){
      list_add(from_vertex->edges, (void*)to, 0);
   }
}


//////////////////////////////Test
/*
void main(){
   graph_t *g = make_graph();

   add_vertex(g, make_vertex("A"));
   add_vertex(g, make_vertex("B"));   
   connect_to(g, "A", "B");
   connect_to(g, "B", "A");

   vertex_t *a = find_vertex(g, "A");
   if( a != NULL ){
      printf("%d\n", has_edge(a, "B"));
      printf("%d\n", has_edge(a, "A"));
   }
}*/
