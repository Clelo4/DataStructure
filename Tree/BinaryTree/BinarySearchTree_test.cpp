#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "BinarySearchTree.h"

int main() {
  BinarySearchTree *tree = new BinarySearchTree();
  int test_data[] = {13, 123, 123, 435, 53, 1023, 1, 123, -13, -133, 12313, 1, 2, 3};
  int len = sizeof(test_data) / sizeof(int);
  for (int i = 0; i < len; ++i) {
    tree->insert_node(new Node(test_data[i]));
  }
  assert(tree->binary_tree_height() == 6);
  assert(tree->find_max()->key == 12313);
  tree->delete_node(tree->search_key(53));
  tree->delete_node(tree->find_min());
  assert(tree->find_min()->key == -13);
  free(tree);
  printf("BinarySearchTree test pass.\n");
  return 0;
}
