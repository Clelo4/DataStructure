#ifndef __SPLAY_H
#define __SPLAY_H

typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
  int data;
  BinTree left;
  BinTree right;
  BinTree parent;
};

BinTree splay_search(BinTree, int);
BinTree splay_insert(BinTree, int);
BinTree splay_delete(BinTree, int);
BinTree __splay(BinTree);

#endif
