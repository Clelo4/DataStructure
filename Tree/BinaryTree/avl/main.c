#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

void printNode(BinTree root) {
  if (!root) return;
  printf("\nprintNode -> %p: %d", root, root->data);
  if (root->left) printNode(root->left);
  if (root->right)  printNode(root->right);
}

int main(void) {
  BinTree root = calloc(1, sizeof(struct TNode));
  root->left = root->right = NULL;
  root->data = 100;
  root->level = tree_level(root);


  root = avl_insert(root, 10);
  root = avl_insert(root, 9);
  root = avl_insert(root, 101);
  root = avl_insert(root, 150);
  root = avl_insert(root, 102);
  root = avl_insert(root, 120);
  root = avl_insert(root, 160);
  root = avl_insert(root, 151);
  root = avl_insert(root, 110);
  root = avl_insert(root, 1);
  root = avl_delete(root, 101);
  root = avl_delete(root, 120);
  root = avl_delete(root, 160);
  root = avl_insert(root, 101);
  root = avl_delete(root, 101);
  root = avl_delete(root, 101);
  root = avl_insert(root, 102);
  printNode(root);
  return 0;
}