#include "binTreeSearch.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main() {
  BinSearchTree T = (BinSearchTree) calloc(1, sizeof(struct BinSearchTree));
  T->root = NULL;
  int testList[] = { 12, 123, 324, 45, 45, 345 };
  int len = sizeof(testList) / sizeof(int);
  for (int i = 0; i < len; ++i) {
    Position z = (Position) calloc(1, sizeof(struct TNode));
    z->key = testList[i];
    z->left = z->right = z->parent = NULL;
    binTreeSearch_insert(T, z);
  }
  Position target = binTreeSearch_find_min(T);
  assert(target->key == 12);
  binTreeSearch_delete(T, target);
  Position searchRes = binTreeSearch_search(T, 45);
  assert(searchRes->key == 45);
  target = binTreeSearch_find_max(T);
  assert(target->key == 345);
  free(T);
}
