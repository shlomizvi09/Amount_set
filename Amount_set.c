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
  for (node_ptr = set->head->next; node_ptr != NULL;
       node_ptr = node_ptr->next) {
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
  double tmp_amount = 0;
  tmp_amount = node_ptr->amount;
  *outAmount = tmp_amount;
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
    AmountSetResult result = asRegister(new_set,
                                        node_ptr_copy_from->element);
    if (result == AS_NULL_ARGUMENT) {
      asDestroy(new_set);
      return NULL; // if element is NULL it's an error?
    }
    Node node_ptr_copy_to =
        getElementNodePtr(new_set,
                          node_ptr_copy_from->element);// TODO : if getElement return NULL ?

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
    if (set->as_compare(element, node_after->element) < 0) {
      break;
      /*loop runs until it reaches a bigger element (by as_compare)
       * or the end of the list (NULL) */
    }
    node_before = node_after;
    node_after = node_after->next;
  }
  Node new_node = malloc(sizeof(*new_node));
  if (new_node == NULL) {
    return AS_OUT_OF_MEMORY;
  }
  new_node->element = set->as_copy(element);
  new_node->amount = 0;
  new_node->next = node_after;
  node_before->next = new_node;
  return AS_SUCCESS;
}

AmountSetResult asDelete(AmountSet set, ASElement element) {
  if (set == NULL || element == NULL) {
    return AS_NULL_ARGUMENT;
  }
  if (!asContains(set, element)) {
    return AS_ITEM_DOES_NOT_EXIST;
  }
  Node node_before = set->head;
  Node node_to_delete = set->head->next;
  while (node_to_delete != NULL) {
    if (set->as_compare(element, node_to_delete->element) == 0) {
      break;
    }
    node_to_delete = node_to_delete->next;
    node_before = node_to_delete;

  }
  assert(node_to_delete != NULL); // because element is in the list
  set->as_free(node_to_delete->element);
  node_before->next = node_to_delete->next;
  free(node_to_delete);

}

AmountSetResult asClear(AmountSet set) {
  if (set == NULL) {
    return AS_NULL_ARGUMENT;
  }
  Node node_ptr = set->head->next;
  while (node_ptr != NULL) {
    Node curr_node = node_ptr;
    set->as_free(curr_node->element);
    node_ptr = curr_node->next;
    free(curr_node);
  }
  return AS_SUCCESS;
}

AmountSetResult asChangeAmount(AmountSet set, ASElement element, const double
amount) {
  assert(set && element);
  if (asContains(set, element) == false) {
    return AS_ITEM_DOES_NOT_EXIST;
  }
  Node node_of_element = getElementNodePtr(set, element);
  if (node_of_element->amount + amount < 0) {
    return AS_INSUFFICIENT_AMOUNT;
  } else {
    node_of_element->amount = node_of_element->amount + amount;
    return AS_SUCCESS;
  }
}

ASElement asGetFirst(AmountSet set) {
  assert(set && set->head->next);
  set->iterator = set->head->next;
  return set->iterator;
}

ASElement asGetNext(AmountSet set) {
  assert(set && set->head->next);
  set->iterator = set->iterator->next;
  return set->iterator;
}
