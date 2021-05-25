#include "print.h"
#include <stdio.h>

int main(void) {
  BinTree root = insert(NULL, 100);
  root = insert(root, 50);
  root = insert(root, 70);
  root = insert(root, 30);
  root = insert(root, 110);
  root = insert(root, 10);
  root = insert(root, 10);
  root = insert(root, 20);
  printf("tree Height %d\n", getHeight(root));
  // inOrderPrint(root);
  printf("new\n");
  printBinTree(root);

  return 0;
}