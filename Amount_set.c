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
        if ((set->head->element) != NULL) {
            free(set->head->element);
        }
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
    for (node_ptr = set->head; node_ptr != NULL; node_ptr = node_ptr->next) {
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
    set->iterator = set->head;
    while (set->iterator) {
        set->iterator = set->iterator->next;
        size++;
    }
    return size;
}

/*AmountSetResult asGetAmount(AmountSet set, ASElement element, double
*outAmount) {
    if (!set || !element || !outAmount) {
        return AS_NULL_ARGUMENT;
    }
    if (asContains(set, element) == false) {
        return AS_ITEM_DOES_NOT_EXIST;
    }


}*/

static Node getElement(AmountSet set,ASElement element){
    assert(set);
    Node node_ptr=set->head;
    while (node_ptr!=NULL){
        if(set->as_compare(node_ptr->element,element)==0){
            return node_ptr;
        }
        node_ptr=node_ptr->next;
    }
    return NULL;
}



/*AmountSetResult asRegister(AmountSet set, ASElement element) {
  if ((set == NULL) || (element == NULL)) {
    return AS_NULL_ARGUMENT;
  }
  Node iterator = set->head->next;
  for (; iterator != NULL; iterator = iterator->next) {

  }
}*/
