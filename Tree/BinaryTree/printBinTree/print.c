#include "print.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

static int** binTreeCoordinateBits = NULL;

BinTree insert(BinTree root, int k) {
  BinTree newNode = calloc(1, sizeof(struct TNode));
  newNode->data = k; newNode->left = newNode->right = NULL;
  if (!root) return newNode;
  
  BinTree target = root;
  while(target) {
    if (k <= target->data) {
      if (target->left) {
        target = target->left;
      } else {
        target->left = newNode;
        break;
      }
    } else {
      if (target->right) {
        target = target->right;
      } else {
        target->right = newNode;
        break;
      }
    }
  }
  
  return root;
}

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

void inOrderPrint(BinTree root) {
  if (!root) return;
  inOrderPrint(root->left);
  printf("%d ", root->data);
  inOrderPrint(root->right);
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
  binTreeCoordinateBits = calloc(height, sizeof(int *));
  for (int i = 0; i < height; i++) {
    binTreeCoordinateBits[i] = calloc(width, sizeof(int));
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