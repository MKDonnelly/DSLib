#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../linked_list/single/slist.h"
#include "../queue/queue.h"

typedef struct{
   slist_head_t list_member;
   char *to;
}edge_t;

#define COLOR_WHITE 0
#define COLOR_GREY 1
#define COLOR_BLACK 2
typedef struct{
   //This structure will be used in
   //two different lists. The graph
   //entity will have a list of vertex_t's
   //and, when searching, we will maintain
   //a queue of vertex_t for BFS.
   slist_head_t graph_member;
   slist_head_t search_member;

   //List of edges of type edge_t
   slist_t *connected_to;

   //used for BFS and DFS searching
   char color;
   int finish;
   char *name;
}vertex_t;

typedef struct{
   slist_t *vertexes;
}graph_t;


edge_t *make_edge(const char *name){
   edge_t *new_edge = malloc(sizeof(edge_t));
   new_edge->to = strdup(name);
   return new_edge;
}

void free_edge(edge_t *e){
   free(e->to);
   free(e);
}

vertex_t *make_vertex(const char *name, int data){
   vertex_t *new_vertex = malloc(sizeof(vertex_t));
   new_vertex->name = strdup(name);
   new_vertex->connected_to = slist_create(edge_t, list_member);
   return new_vertex;
}

graph_t *make_graph(){
   graph_t *g = malloc(sizeof(graph_t));
   g->vertexes = slist_create(vertex_t, graph_member);
   return g;
}


void add_vertex(graph_t *g, vertex_t *v){
   slist_add(g->vertexes, v, 0);
}

vertex_t *get_vertex(graph_t *g, const char *name){
   for(vertex_t *gnode = slist_get(g->vertexes, 0);
       gnode != NULL; 
       gnode = slist_next(g->vertexes, gnode) ){

      if( strcmp(gnode->name, name) == 0 )
         return gnode;
   }
   return NULL;
}

int connect_to(graph_t *g, const char *from, const char *to){
   vertex_t *from_vertex = get_vertex(g, from);
   if( from_vertex != NULL ){
      slist_append(from_vertex->connected_to, make_edge(to));
      return 0;
   }else{
      return 1;
   }
}

slist_t *get_edges(vertex_t *v){
   return v->connected_to;
}

int hash_edge(vertex_t *v, const char *edge){
   slist_t *edges = get_edges(v);
   for(edge_t *e = slist_get(edges, 0); e != NULL; e = slist_next(edges, e) ){
      if( strcmp(e->to, edge) == 0)
         return 1;
   }
   return 0;
}

typedef struct{
   slist_t slist_member;
   vertex_t *ref;
}vref_t;

vref_t *make_vref(vertex_t *v){
   vref_t *new_vref = malloc(sizeof(vref_t));
   new_vref->ref = v;
   return new_vref;
}

void bfs(graph_t *g, const char *start){
   //color each node white
   for(vertex_t *v = slist_get(g->vertexes, 0); v != NULL; 
       v = slist_next(g->vertexes, v)){
      v->color = COLOR_WHITE;
   }

   queue_t *queue = create_queue(vref_t, slist_member);
   enqueue_queue(queue, make_vref(get_vertex(g, start)));
   while( len_queue(queue) > 0 ){
      vref_t *current = dequeue_queue(queue);
      current->ref->color = COLOR_GREY;
      printf("Visiting %s\n", current->ref->name);
      if( current->ref->connected_to != NULL ){
         for(edge_t *e = slist_get(current->ref->connected_to, 0);
             e != NULL; 
             e = slist_next(current->ref->connected_to, e)){
            vertex_t *node = get_vertex(g, e->to);
            if( node->color == COLOR_WHITE )
               enqueue_queue(queue, make_vref(node));
         }
      }
   }
}

void __dfs(graph_t *g, const char *start, int *count){
   vertex_t *node = get_vertex(g, start);
   node->color = COLOR_GREY;
   for(edge_t *child = slist_get(get_edges(node), 0); child != NULL; 
       child = slist_next(get_edges(node), child) ){
      vertex_t *to = get_vertex(g, child->to);
      if( to->color == COLOR_WHITE ){
         to->color = COLOR_GREY;
         __dfs(g, child->to, count);
      }
   }
   count++;
   node->finish = (*count)++;
   node->color = COLOR_BLACK;
   printf("Visiting %s\n", node->name);
}

void dfs(graph_t *g, const char *start){
   //color each node white
   for(vertex_t *v = slist_get(g->vertexes, 0); v != NULL; 
       v = slist_next(g->vertexes, v)){
      v->color = COLOR_WHITE;
      v->finish = -1;
   }
   int count = 1;
   __dfs(g, start, &count);
}

/*void graph_transpose(graph_t *g){
   for(vertex_t *vertex = slist_get(g->vertexes, 0); vertex != NULL;
       vertex = slist_next(g->vertexes, vertex) ){
      for(edge_t *edge = slist_get(vertex->connected_to); edge != NULL;
          edge = slist_next(vertex->connected_to, edge) ){
         char *from = vertex->name;
         char *to 
      }
   }
}*/

void main(){
   graph_t *g = make_graph();
   add_vertex(g, make_vertex("first", 0));
   add_vertex(g, make_vertex("second", 1));
   add_vertex(g, make_vertex("third", 2));
   add_vertex(g, make_vertex("fourth", 3));
   add_vertex(g, make_vertex("fifth", 4));
   add_vertex(g, make_vertex("sixth", 5));
   add_vertex(g, make_vertex("seventh", 6));
   add_vertex(g, make_vertex("eighth", 7));

   connect_to(g, "first", "fourth");
   connect_to(g, "second", "fourth");
   connect_to(g, "third", "fourth");
 
   connect_to(g, "fourth", "fifth");

   connect_to(g, "fifth", "sixth");
   connect_to(g, "fifth", "seventh");
   connect_to(g, "fifth", "eighth");

   dfs(g, "first");

   for(vertex_t *v = slist_get(g->vertexes, 0); v != NULL; v = slist_next(g->vertexes, v)){
      printf("%s: %d\n", v->name, v->finish);
   }

/*   add_vertex(g, make_vertex("first", 0));
   add_vertex(g, make_vertex("second", 1));
   add_vertex(g, make_vertex("third", 2));
   add_vertex(g, make_vertex("fourth", 3));
   add_vertex(g, make_vertex("fifth", 4));
   add_vertex(g, make_vertex("sixth", 5));
   add_vertex(g, make_vertex("seventh", 6));
   add_vertex(g, make_vertex("eighth", 7));

   connect_to(g, "first", "second");
   connect_to(g, "first", "third");
   connect_to(g, "first", "fourth");
   connect_to(g, "second", "fifth");
   connect_to(g, "fifth", "sixth");
   connect_to(g, "fifth", "seventh");
   connect_to(g, "fourth", "eighth");
   connect_to(g, "seventh", "first");

   //bfs(g, "first"); 
   dfs(g, "first");*/
}
