#include "skip_list.h"
#include <stdio.h>

int main(void) {
  Skiplist list = Skiplist();
  list.add(1);
  for (int i = 0; i < 10; i++) {
    list.add(i * i);
  }
  list.erase(25);
  printf("%d\n", list.search(25));
  return 0;
}