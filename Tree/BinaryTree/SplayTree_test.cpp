#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "SplayTree.h"

int main() {
  SplayTree *tree = new SplayTree();
  int test_data[] = {13, 123, 123, 435, 53, 1023, 1, 123, -13, -133, 12313, 1, 2, 3};
  const int len = sizeof(test_data) / sizeof(int);
  for (int i = 0; i < len; ++i) {
    tree->insert_node(new Node(test_data[i]));
  }
  assert(tree->binary_tree_height() == 6);
  assert(tree->find_max()->key == 12313);
  assert(tree->search_key(12313)->key == 12313);
  tree->delete_node(tree->search_key(12313));
  tree->delete_node(tree->find_min());
  assert(tree->find_min()->key == -13);
  free(tree);
  printf("SplayTree test pass.\n");
  return 0;
}
