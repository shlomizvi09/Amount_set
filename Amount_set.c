
#include "Amount_set.h"
#include <stdlib.h>

typedef struct node_t {
  ASElement element;
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
  return new_set;
}

AmountSetResult asRegister(AmountSet set, ASElement element) {
  if ((set == NULL) || (element == NULL)) {
    return AS_NULL_ARGUMENT;
  }
  Node iterator = set->head->next;
  for (; iterator != NULL; iterator = iterator->next) {

  }
}
