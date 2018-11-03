#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

typedef struct automata{
   graph_t *graph;
   vertex_t *start;
   vertex_t *final;
   vertex_t *current;
}automata_t;

automata_t *automata_create(){
   automata_t *new_automata = malloc(sizeof(automata_t));
   new_automata->graph = graph_create();
   new_automata->start = new_automata->final = 
                            new_automata->current = NULL;
   return new_automata;
}

void automata_set_start(automata_t *a, const char *name){
   a->start = a->current = graph_find_vertex(a->graph, name);
}

void automata_set_final(automata_t *a, const char *name){
   a->final = graph_find_vertex(a->graph, name);
}

int automata_transition(automata_t *a, char input){
   //convert a char into a char*
   char t[2] = {input, 0};
   if( vertex_has_edge(a->current, t) ){
      a->current = graph_find_vertex(a->graph, t);
      return 1;
   }else{
      return 0;
   }
}

int automata_in_final_state(automata_t *a){
   return a->final == a->current;
}

int automata_accepted(automata_t *a, char *input){
   for(int i = 0; i < strlen(input); i++){
      if( ! automata_transition(a, input[i]) )
         return 0;
   }
   if( automata_in_final_state(a) )
      return 1;
   else
      return 0;
}

void automata_add_node(automata_t *a, const char *name){
   graph_add_vertex(a->graph, vertex_create(name));
}

void automata_add_transition(automata_t *a, const char *from, 
                                            const char *to){
   graph_connect_vertexes(a->graph, from, to);
}

void main(){
   automata_t *a = automata_create();
   automata_add_node(a, "a");

   automata_set_start(a, "a");
   automata_set_final(a, "a");

   automata_add_transition(a, "a", "a");

   char input[] = "aaaaa";
   printf("%d\n", automata_accepted(a, input));
}
