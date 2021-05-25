#ifndef _PRINT_H
#define _PRINT_H

typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
    int data;
    BinTree left;
    BinTree right;
};

BinTree insert(BinTree root, int k);
int getBinTreeXCoordinate(BinTree root,int x, int y);
int getHeight(BinTree root);
void inOrderPrint(BinTree root);
int getBinTreeLeafNum(BinTree root);
void printBinTree(BinTree root);

#endif