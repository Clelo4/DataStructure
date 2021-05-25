#ifndef binTreeSearch_h
#define binTreeSearch_h

#include <stdio.h>

typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
    int data;
    BinTree left;
    BinTree right;
};

BinTree binTreeSearch_insert(BinTree root, int data);
BinTree binTreeSearch_search(BinTree root, int data);
void binTreeSearch_delete(BinTree root, int data);
BinTree binTreeSearch_find_min(BinTree root);
BinTree binTreeSearch_find_max(BinTree root);

#endif