
#include "Amount_set.h"

typedef struct node_t {

} *Node;

typedef struct AmountSet_t {
  CopyASElement copy_as_element_ = NULL;
  FreeASElement free_as_element_ = NULL;
  CompareASElements compare_as_elements_ = NULL;

};

AmountSet asCreate(CopyASElement copyElement,
                   FreeASElement freeElement,
                   CompareASElements compareElements) {

}