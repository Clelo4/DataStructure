#ifndef avl_h
#define avl_h
#include <stdio.h>

typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
    int data;
    BinTree left;
    BinTree right;
    BinTree parent;
    int level;
};

int tree_level(BinTree parent);
BinTree avl_search(BinTree, int);
BinTree avl_insert(BinTree, int);
BinTree avl_delete(BinTree, int);

#endif