#include <stdlib.h>
#include <stdio.h>
#include "redBlack.h"

void printNode(BinTree root) {
  if (!root) return;
  printf("\nprintNode -> %p: %d ", root, root->data);
  if (root->color == BLACK) {
    printf("balck");
  } else {
    printf("red");
  }
  if (root->left) printNode(root->left);
  if (root->right)  printNode(root->right);
}

int main(void) {
  BinTree root = calloc(1, sizeof(struct TNode));
  root->left = root->right = root->parent = NULL;
  root->data = 100;
  root->color = BLACK;
  red_black_insert(root, 10);
  red_black_insert(root, 9);
  BinTree newRoot = root->parent;
  red_black_insert(root, 101);
  red_black_insert(root, 150);
  red_black_insert(root, 102);
  red_black_insert(root, 120);
  red_black_insert(root, 160);
  red_black_insert(root, 151);
  red_black_insert(root, 110);
  red_black_insert(root, 1);
//   avl_delete(root, 101);
//   avl_delete(root, 120);
//   avl_delete(root, 160);
//   red_black_insert(root, 101);
//   avl_delete(root, 101);
//   avl_delete(root, 101);
//   red_black_insert(root, 102);
  printNode(newRoot);
  return 0;
}