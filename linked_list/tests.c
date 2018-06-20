#include <stdio.h>
#include <stdlib.h>
#include "genericll.h"


typedef struct{
   list_head_t *next;
   int data;
}test_struct_t;

int test_list_init(){
   list_t *new_list = list_create( test_struct_t, next );
   
   if( list_head(new_list) != NULL ){
      printf("%s: Head is not NULL!\n", __FUNCTION__);
      return 1;
   }
   if( list_len(new_list) != 0 ){
      printf("%s: Length is not 0!\n", __FUNCTION__);
      return 1;
   }
   if( list_ptroffset(new_list) != 0 ){
      printf("%s: Ptr offset is not 0!\n", __FUNCTION__);
      return 1;
   }

   free(new_list);
   return 0;
}

int test_free_empty_list(){
   list_t *new_list = list_create(test_struct_t, next);

   list_free(new_list, NULL);

   if( new_list != NULL ){
      printf("%s: List not NULL!\n", __FUNCTION__);
      return 1;
   }
   return 0;
}

int test_free_full_list(){
   list_t *new_list = list_create(test_struct_t, next);
   
   test_struct_t *first = malloc(sizeof(test_struct_t));
   test_struct_t *second = malloc(sizeof(test_struct_t));
   test_struct_t *third = malloc(sizeof(test_struct_t));
   list_add(new_list, first, 0);
   list_add(new_list, second, 1);
   list_add(new_list, third, 2);

   list_free(new_list, free);

   if( new_list != NULL ){
      printf("%s: List not NULL!\n", __FUNCTION__);
      return 1;
   }
   return 0;
}


int test_add_get_single_element(){
   list_t *new_list = list_create(test_struct_t, next);

   test_struct_t *new_element = malloc(sizeof(test_struct_t));
   list_add( new_list, new_element, 0 );
   test_struct_t *retrieved = list_get(new_list, 0, test_struct_t);
   
   if( new_element != retrieved ){
      printf("%s: Retrived element not correct!\n", __FUNCTION__);
      list_free(new_list, free);
      return 1;
   }
   list_free(new_list, free);
   return 0;
}

int test_get_null_element(){
   list_t *new_list = list_create(test_struct_t, next);

   if( list_get(new_list, 0, test_struct_t) != NULL ){
      printf("%s: Return not NULL!\n", __FUNCTION__);
      list_free(new_list, NULL);
      return 1;
   }
   list_free(new_list, NULL);
   return 0;
}

int test_len_value_add(){
   list_t *new_list = list_create(test_struct_t, next);

   for(int i = 0; i < 10; i++){
      test_struct_t *test = malloc(sizeof(test_struct_t));
      if( list_len(new_list) != i ){
         printf("%s: Failed len test on iter %d\n", __FUNCTION__, i);
         printf("Expected %d, got %d\n", i, list_len(new_list));
         list_free( new_list, free );
         return 1;
      }
      list_add(new_list, test, 0);
   } 
   list_free(new_list, free);
   return 0;
}

int test_len_value_get(){
   list_t *new_list = list_create(test_struct_t, next);

   for(int i = 0; i < 10; i++){
      test_struct_t *test = malloc(sizeof(test_struct_t));
      list_add(new_list, test, i);
      int current_len = list_len(new_list);
      test_struct_t *get = list_get(new_list, i, test_struct_t);
      if( current_len != list_len(new_list)){
         printf("%s: Length changed on get!\n", __FUNCTION__);
         list_free(new_list, free);
         return 1;
      }
   }
   list_free(new_list, free);
   return 0;
}

int test_list_foreach(){
   list_t *new_list = list_create(test_struct_t, next);
   
   //Add in elements numbered 0..3
   for(int i = 0; i < 3; i++){
      test_struct_t *t = malloc(sizeof(test_struct_t));
      t->data = i;
      list_add(new_list, t, i);
   }


   //Loop over each element and check
   int check = 0;
   list_foreach(new_list, e){
      test_struct_t *s = list_ptrof(new_list, e, test_struct_t);
      if( s->data != check ){
         printf("%s: Wrong data on iter %d\n", __FUNCTION__, check);
         printf("Expected %d, got %d\n", check, s->data);
         list_free(new_list, free);
         return 1;
      }
      check++;
   }
   list_free(new_list, free);
   return 0;
}

int test_list_ordering(){
   list_t *new_list = list_create(test_struct_t, next);

   //Place 3 elements
   test_struct_t *first = malloc(sizeof(test_struct_t));
   test_struct_t *second = malloc(sizeof(test_struct_t));
   test_struct_t *third = malloc(sizeof(test_struct_t));
   list_add(new_list, first, 0);
   list_add(new_list, second, 1);
   list_add(new_list, third, 2);

   //Test inserting a new element between the second and third
   test_struct_t *test = malloc(sizeof(test_struct_t));
   list_add(new_list, test, 2);

   if( list_get(new_list, 2, test_struct_t) != test){
      printf("%s: Got wrong element!\n", __FUNCTION__);
      list_free(new_list, free);
      return 1;
   }
   return 0;
}

int (*tests[])() = {
   test_list_init,
   test_free_empty_list, 
   test_free_full_list,
   test_add_get_single_element,
   test_len_value_add,
   test_list_foreach,
   test_list_ordering,
};

void main(){
   for(int i = 0; i < (sizeof(tests) / sizeof(tests[0])); i++){
      if( tests[i]() != 0 ){
         printf("Test #%d Failed!\n", i); 
         exit(1);
      }
   }
   printf("All tests passed.\n");
}
