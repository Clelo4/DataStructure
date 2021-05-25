#include "Print.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int getBinTreeXCoordinate(BinTree root,int x, int y);
int getHeight(BinTree root);
int getBinTreeLeafNum(BinTree root);

static int** binTreeCoordinateBits = NULL;

// 返回树root最右节点的x坐标
int getBinTreeXCoordinate(BinTree root, int x, int y) {
  if (!root) return x;
  int root_x = getBinTreeXCoordinate(root->left, x, y + 1);
  int root_y = y;
  binTreeCoordinateBits[root_y][root_x] = root->data;
  printf("save Node %d in (%d, %d)\n", root->data, root_x, root_y);
  int root_right_x = getBinTreeXCoordinate(root->right, root_x + 1, y + 1);
  return root_right_x;
}

int getHeight(BinTree root) {
  if (!root) return 0;
  int left_height = getHeight(root->left);
  int right_height = getHeight(root->right);
  return ((left_height > right_height) ? left_height : right_height) + 1;
}

int getBinTreeLeafNum(BinTree root) {
  return pow(2, getHeight(root) - 1);
}

void printBinTree(BinTree root) {
  int height = getHeight(root);
  int width = getBinTreeLeafNum(root);
  printf("width: %d, height: %d\n", width, height);
  binTreeCoordinateBits = (int**) calloc(height, sizeof(int *));
  for (int i = 0; i < height; i++) {
    binTreeCoordinateBits[i] = (int*) calloc(width, sizeof(int));
    memset(binTreeCoordinateBits[i], -1, width * sizeof(int));
  }
  getBinTreeXCoordinate(root, 0, 0);
  for (int i = 0; i < height; i++) {
    int *first = binTreeCoordinateBits[i];
    // printf("first %p\n", first);
    for (int j = 0; j < width; j++) {
       printf(" %d ", first[j]);
    }
    printf("\n");
  }

  // free binTreeCoordinateBits
  for (int i = 0; i < height; i++) {
    free(binTreeCoordinateBits[i]);
  }
}

void inOrderPrint(BinTree root) {
  if (!root) return;
  inOrderPrint(root->left);
  printf("%d=>color: %d  ", root->data, root->color);
  inOrderPrint(root->right);
}
