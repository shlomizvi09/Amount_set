
#include "Amount_set.h"
#include <stdlib.h>

typedef struct node_t {
  ASElement element;
  double amount;
  struct node_t *next;
} *Node;

typedef struct AmountSet_t {
  CopyASElement as_copy;
  FreeASElement as_free;
  CompareASElements as_compare;
  Node head;
} *AmountSet;

AmountSet asCreate(CopyASElement copyElement,
                   FreeASElement freeElement,
                   CompareASElements compareElements) {
  if (copyElement == NULL || freeElement == NULL || compareElements == NULL) {
    return NULL;
  }
  AmountSet new_set = malloc(sizeof(*new_set));
  if (new_set == NULL) {
    return NULL;
  }
  new_set->as_compare = compareElements;
  new_set->as_free = freeElement;
  new_set->as_copy = copyElement;
  new_set->head = malloc(sizeof(*(new_set->head)));
  if (new_set->head == NULL) {
    free(new_set);
    return NULL;
  }
  new_set->head->next = NULL;
  new_set->head->element = NULL;
  new_set->head->amount = 0;
  return new_set;
}
void asDestroy(AmountSet set) {
  if (!set) {
    return;
  }
  Node temp_ptr = set->head;
  Node temp_ptr2;
  while (temp_ptr) {
    temp_ptr2 = temp_ptr;
    free(temp_ptr);
    temp_ptr = temp_ptr2->next;
  }
}

AmountSetResult asRegister(AmountSet set, ASElement element) {
  if ((set == NULL) || (element == NULL)) {
    return AS_NULL_ARGUMENT;
  }
  Node iterator = set->head->next;
  for (; iterator != NULL; iterator = iterator->next) {

  }
}

bool asContains(AmountSet set, ASElement element) {
  if (set == NULL || element == NULL || set->head == NULL) {
    return false;
  }
  for (Node node_ptr = set->head; node_ptr != NULL; node_ptr = node_ptr->next) {
    if (node_ptr->element == NULL) {
      return false;
    }
    if (set->as_compare(element, node_ptr->element) == 0) {
      return true;
    }
  }

}
