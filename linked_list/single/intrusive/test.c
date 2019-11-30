#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct test{
   struct test *next;
   int d;
}test_t;



void test_set_next(void *test_obj, void *new_next){
   ((test_t*)test_obj)->next = new_next;
}

void *test_get_next(void *test_obj){
   return ((test_t*)test_obj)->next;
}

test_t *test_make(int d){
   test_t *t = malloc(sizeof(test_t));
   t->d = d;
   return t;
}

////////////////Actual tests

//Make sure list is initilized to sane defaults
void test_list_initilization(){
   list_t *l = list_create(test_get_next, test_set_next);

   assert( list_len(l) == 0 );
   assert( list_rmi(l, 0) == NULL );
   assert( list_get(l, 0) == NULL );

   list_free(l, free);
}

void test_list_add_and_get(){
   list_t *l = list_create(test_get_next, test_set_next);

   list_add(l, test_make(99), 0);
   assert(list_len(l) == 1);

   test_t *retrieved = list_get(l, 0);

   assert(retrieved->d == 99);
   assert(list_len(l) == 1);

   list_free(l, free);
}

void test_list_add_and_rmi(){
   list_t *l = list_create(test_get_next, test_set_next);

   list_add(l, test_make(111), 0);
   test_t *removed = list_rmi(l, 0);

   assert(removed->d == 111);
   assert(list_len(l) == 0);

   //free(removed);
   list_free(l, free);
}

void test_list_length(){
   list_t *l = list_create(test_get_next, test_set_next);

   for(int i = 0; i < 3; i++){
      test_t *t = test_make(i);
      list_add(l, t, 0);
      assert(list_len(l) == i+1);
   }

   for(int i = 0; i < 3; i++){
      test_t *ret = list_rmi(l, 0);
      assert(list_len(l) == 2-i);
      assert(ret->d + i == 2);
   }

   list_free(l, free);   
}

void test_list_rmn_and_get(){
   list_t *l = list_create(test_get_next, test_set_next);

   for(int i = 0; i < 10; i++){
      test_t *t = test_make(i);
      //append new element
      list_add(l, t, list_len(l));
      
      //verify get works
      test_t *ret = list_get(l, i);
      assert( ret->d == i );
   }

   //Remove the 7th node
   test_t *seventh = list_get(l, 6);
   assert( seventh->d == 6 );

   list_rmn(l, seventh);
   free(seventh);

   //Make sure the node that is now in position
   //6 is the node that came after node 7
   seventh = list_get(l, 6);
   assert(seventh->d == 7);
}

void main(){
   test_list_initilization();
   test_list_add_and_get();
   test_list_length();
   test_list_add_and_rmi();


   printf("All tests passed!\n");
}
