#include <stdlib.h>
#include <assert.h>

typedef struct node_t {
  ASElement element;
  double amount;
  struct node_t *next;
} *Node;

static Node getElementNodePtr(AmountSet set, ASElement element);

typedef struct AmountSet_t {
  CopyASElement as_copy;
  FreeASElement as_free;
  CompareASElements as_compare;
  Node head;
  Node iterator;
} *AmountSet;

AmountSetResult asClear(AmountSet set);


