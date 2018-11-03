#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void main(){
   list_t new_list = list_init();

   list_add(&new_list, (void*)"first", 0);
   list_add(&new_list, (void*)"second", 1);
   list_add(&new_list, (void*)"third", 2);

   list_iter(&new_list, iter){
      printf("Got %s\n", (char*)iter->data);
   } 
}
