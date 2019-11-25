#include "Amount_set.h"
#include <stdio.h>
#include <stdlib.h>

ASElement copyFunction(ASElement element) {
  if (element == NULL) {
    return NULL;
  }
  int *new_element = malloc(sizeof(int));
  if (new_element == NULL) {
    return NULL;
  }
  *new_element = *(int *) element;
  return new_element;
}
ASElement freeFunction(ASElement element) {
  free(element);
}
int compareFunction(ASElement a, ASElement b) {
  int new_a = *(int *) a;
  int new_b = *(int *) b;
  return a > b ? 1 : (a < b ? -1 : 0);
}

int main() {

  return 0;
}