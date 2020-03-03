#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "list.h"

int main( int argc, char* argv[] )
{
  // test the create function
  list_t* list = list_create();
  list_t* list1 = list_create();
  list_t* list2 = list_create();
  list_t* list3 = list_create();
  
  //// check to see if the create function did everything it was supposed to
  if( list == NULL )
    {
      printf( "1 create: create failed to malloc\n" );
      return 1;
    }

  if( list->head != NULL )
    {
      printf( "2 create: head is not null!\n" );
      return 1;
    }

  if( list->tail != NULL )
    {
      printf( "3 create: tail is not null!\n" );
      return 1;
    }

  // now test all the other functions (except list_print) to see if
  // they do what they are supposed to


  //// Test the element create function using
  element_t * ele = element_create(4);
  element_t * ele2 = element_create(5);
  ele->next = ele2;
  free(ele);
  ele = element_create(4);

  
  
  

  if(ele == NULL){
    printf("4 element create: failed to malloc\n");
    return 1;
  }
  if(ele->val != 4){
    printf("5 element create: wrong value assigned\n");
    return 1;
  }

  if(ele->next != NULL){
    printf("6 element create: next is not NULL\n");
    return 1;
  }

   printf("passed element_create test!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");



  //// Test the append function using list1
  int la; //list append
  printf("Appending 0th element in list 1\n");
  la = list_append(list1, 0);
  list_print(list1);
  if (la == 1){
    printf("8 List append: failed to malloc\n");
    return 1;
  }

  if(list1->head->val != 0 || list1->tail->val != 0) {
    printf("9 list append:error at first assignment\n");
    return 1;
  }

  for (int i = 1; i < 10; i++){
    printf("Appending %dth element in list 1\n", i);
    la = list_append(list1, i);
    list_print(list1);
    if (la == 1){
      printf("10 List append: failed to malloc\n");
      return 1;
    }
    if(list1->head->val == i){
      printf("11 List append: failed to append\n");
      return 1;
    }
    if(list1->tail->val != i){
      printf("12 List append: failed to append\n");
      return 1;
    }
  }
  printf("passed List_append test !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");


  //// Test the prepend function using list 2
  printf("Prepending 0th element in list 2\n");
  int lp = list_prepend(list2, 0);
  list_print(list2);
  if (lp == 1){
    printf("13 list_prepend: failed to malloc\n");
    return 1;
  }

  if(list2->head == NULL || list2->tail == NULL){
    printf("14 List prepend: failed to prepend\n");
    return 1;
  }

  for (int i = 1; i < 10; i++){
    printf("Prepending %dth element in list 2\n", i);
    lp = list_prepend(list2, i);
    list_print(list2);
    if(lp == 1){
      printf("15 List prepend: failed to malloc\n");
      return 1;
    }
    if(list2->tail->val == i){
      printf("16 List prepend: failed to prepend\n");
      return 1;
    }
    if(list2->head->val != i){
      printf("17 List prepend: failed to prepend\n");
      return 1;
    }
  
  }
  printf("passed List_prepend test!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

  //// Test the index function using list lsit1 list3
  element_t * li = list_index(list3, 1);
  if(li != NULL){
    printf("18 failed to index empty list\n");
    return 1;
  }

  list_append(list3, 100);
  li = list_index(list3, 0);
  list_print(list3);
  if(li == NULL){
    printf("19 failed to index\n");
    return 1;
  } 

  li = list_index(list3, 1);
  if(li != NULL){
    printf("19 failed to index\n");
    return 1;
  }

  li = list_index(list3, 2);
  if(li != NULL){
    printf("19 failed to index\n");
    return 1;
  } 

  li = list_index(list3, 0);
  if(li != list3->head || li != list3->tail){
    printf("20 failed to index\n");
    return 1;
  }

  list_print(list1);

  for (int i = 0; i < 10; i++){
    li = list_index(list1, i);
    printf("21 Comparing i=%d and li=%d\n", i, li->val);
    if(li->val != i){
      printf("22 failed to index\n");
      return 1;
    }
  }
  printf("passed List_index test\n");

  //// Test the detroy function
  list_destroy(list);
  list_destroy(list1);
  list_destroy(list2);
  list_destroy(list3);



 //you code goes here
  
  return 0; // tests pass
}
