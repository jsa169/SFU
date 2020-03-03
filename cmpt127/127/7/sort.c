#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "list.h"	
void list_addback(list_t * list, list_t * sub){
  if(sub->head == NULL)
    return;
  if (list->head == NULL)
    *list = *sub;
  else{
    list->tail->next = sub->head;
    list->tail = sub->tail;
  }
  free(sub);
}

void list_sort(list_t* list){
  //Base case where size of array is 0 or 1
  if(list->head == NULL || list->head->next == NULL){
    return;
  }

  //Use head as pivot point
  int piv = list->head->val;
  list->head = list->head->next;

  //Create two new lists
  list_t * right = list_create();
  list_t * left = list_create();

  element_t * current = list->head;

  //Split into two array base on their value compaired to piv
  while (current != NULL){
    if(current->val <= piv)
      list_append(left, current->val);
    else
      list_append(right, current->val);
    free(current);
    current = current->next;
  }

  //Empty the orightnal array
  list->head = NULL;
  list->tail = NULL;

  //Recursivelly call sorting function
  list_sort(right);
  list_sort(left);

  //Addback the two side together into original array
  list_addback(list, left);
  list_append(list, piv);
  list_addback(list, right);

}