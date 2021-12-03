#ifndef binTreeSearch_h
#define binTreeSearch_h

#include <stdio.h>

typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
    int key;
    Position parent;
    Position left;
    Position right;
};

typedef struct BinSearchTree {
    Position root;
} *BinSearchTree;

void binTreeSearch_insert(BinSearchTree T, Position z);
Position binTreeSearch_search(BinSearchTree T, int key);
void binTreeSearch_delete(BinSearchTree T, Position z);
Position binTreeSearch_find_min(BinSearchTree T);
Position binTreeSearch_find_max(BinSearchTree T);

#endif