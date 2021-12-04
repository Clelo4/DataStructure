#include <assert.h>
#include <stdio.h>
#include "BinaryTree.h"

int main() {
  BinaryTree *tree = new BinaryTree();
  tree->root = new Node(1);
  Node *target = tree->root;
  target->left = new Node(2);
  target->left->left = new Node(21);
  target->left->left->right = new Node(211);
  target->right = new Node(3);
  target = target->right;
  target->left = new Node(4);
  target->right = new Node(5);
  target->right->right = new Node(6);
  target->right->right->right = new Node(7);
  printf("level_order_traversal output: \t");
  tree->level_order_traversal();
  printf("\nlevel_order_traversal expected output: \t1 2 3 21 4 5 211 6 7\n");
  printf("pre_order_traversal output: \t");
  tree->pre_order_traversal();
  printf("\npre_order_traversal expected output: \t1 2 21 211 3 4 5 6 7\n");
  printf("in_order_traversal output: \t");
  tree->in_order_traversal();
  printf("\nin_order_traversal expected output: \t21 211 2 1 4 3 5 6 7\n");
  printf("post_order_traversal output: \t");
  tree->post_order_traversal();
  printf("\npost_order_traversal expected output: \t211 21 2 4 7 6 5 3 1\n");
  free(tree);
  return 0;
}
