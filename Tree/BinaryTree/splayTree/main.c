#include <stdlib.h>
#include <stdio.h>
#include "splay.h"

void printNode(BinTree root) {
  if (!root) return;
  printf("\nprintNode -> %p: %d parent: %d", root, root->data, (root->parent) ? (root->parent->data) : -1);
  if (root->left) printNode(root->left);
  if (root->right)  printNode(root->right);
}

int main(void) {
  BinTree root = calloc(1, sizeof(struct TNode));
  root->left = root->right = root->parent = NULL;
  root->data = 100;

  root = splay_insert(root, 10);
  root = splay_insert(root, 9);
  root = splay_insert(root, 101);
  root = splay_insert(root, 150);
  root = splay_insert(root, 102);
  root = splay_insert(root, 120);
  root = splay_insert(root, 160);
  root = splay_insert(root, 151);
  root = splay_insert(root, 110);
  root = splay_insert(root, 1);
  root = splay_delete(root, 101);
  root = splay_delete(root, 1);
  root = splay_delete(root, 1);
  root = splay_delete(root, 120);
  printNode(root);
  return 0;
}