#include "Amount_set.h"
#include <stdlib.h>
#include <assert.h>

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
  Node iterator;
} *AmountSet;
static Node findElementSpot(AmountSet set, ASElement element,
                            Node node_before, Node node_after) {
  if (set == NULL || element == NULL) {
    return NULL;
  }
  Node curr_ptr = set->head->next;
  Node prev_ptr = set->head;
  while (curr_ptr != NULL) {
    if (set->as_compare(element, curr_ptr->element) < 0) {

    }
  }
}
static Node getElementNodePtr(AmountSet set, ASElement element) {
  if (set == NULL || element == NULL) {
    return NULL;
  }
  Node node_ptr = set->head->next;
  while (node_ptr != NULL) {
    if (set->as_compare(node_ptr->element, element) == 0) {
      return node_ptr;
    }
    node_ptr = node_ptr->next;
  }
  return NULL;
}
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
  if (set == NULL) {
    return;
  }
  Node temp_ptr = set->head;
  Node temp_ptr2;
  while (temp_ptr) {
    temp_ptr2 = temp_ptr->next;
    free(set->head->element);
    free(temp_ptr);
    temp_ptr = temp_ptr2;
  }
  free(set);
}
bool asContains(AmountSet set, ASElement element) {
  if (set == NULL || set->head == NULL || element == NULL) {
    return false;
  }
  Node node_ptr;
  for (node_ptr = set->head->next; node_ptr != NULL; node_ptr = node_ptr->next) {
    if (node_ptr->element == NULL) {
      return false;
    }
    if (set->as_compare(element, node_ptr->element) == 0) {
      return true;
    }
  }
  assert(node_ptr);
}
int asGetSize(AmountSet set) {
  assert(set);
  int size = 0;
  set->iterator = set->head->next;
  while (set->iterator) {
    set->iterator = set->iterator->next;
    size++;
  }
  return size;
}
AmountSetResult asGetAmount(AmountSet set, ASElement element, double
*outAmount) {
  Node node_ptr;
  if (!set || !element || !outAmount) {
    return AS_NULL_ARGUMENT;
  }
  if (asContains(set, element) == false) {
    return AS_ITEM_DOES_NOT_EXIST;
  }
  node_ptr = getElementNodePtr(set, element);
  *outAmount = node_ptr->amount;
  return AS_SUCCESS;
}
AmountSet asCopy(AmountSet set) {
  if (set == NULL) {
    return NULL;
  }
  AmountSet new_set = asCreate(set->as_copy, set->as_free, set->as_compare);
  if (new_set == NULL) {
    return NULL;
  }
  Node node_ptr_copy_from = set->head->next;
  while (node_ptr_copy_from != NULL) {
    AmountSetResult result = asRegister(new_set, node_ptr_copy_from->element);
    if (result == AS_NULL_ARGUMENT) {
      return NULL; // if element is NULL it's an error? list is over ?
    }
    Node node_ptr_copy_to =
        getElementNodePtr(new_set, node_ptr_copy_from->element);
    assert(node_ptr_copy_to != NULL && node_ptr_copy_to->next == NULL);
    node_ptr_copy_to->amount = node_ptr_copy_from->amount;
    node_ptr_copy_from = node_ptr_copy_from->next;
  }
}
AmountSetResult asRegister(AmountSet set, ASElement element) {
  if (set == NULL || element == NULL) {
    return AS_NULL_ARGUMENT;
  }
  if (asContains(set, element)) {
    return AS_ITEM_ALREADY_EXISTS;
  }
  Node node_before = set->head;
  Node node_after = set->head->next;
  while (node_after != NULL) {
    if (set->as_compare(element, node_after->element) < 0){
      node_before->next=
    }
  }
}

AmountSetResult asChangeAmount(AmountSet set, ASElement element, const double
amount){
    assert(set && element);
    if (asContains(element)==false){
        return AS_ITEM_DOES_NOT_EXIST;
    }

}