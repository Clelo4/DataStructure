#ifndef __RED_BLACK_H
#define __RED_BLACK_H

#include <stdlib.h>

using namespace std;

// （1）树根为黑色
// （2）外部节点：均为黑色
// （3）其余节点：若为红节点，则只能有黑孩子
// （4）外部节点到根：途中黑节点树木相等

typedef enum RB_TREE_COLOR {
  BLACK,
  RED,
} RB_TREE_COLOR;

typedef struct TNode* BinTreeNode;
struct TNode {
  int data;
  BinTreeNode left;
  BinTreeNode right;
  BinTreeNode parent;
  RB_TREE_COLOR color;
  TNode(int v,
    BinTreeNode l = NULL,
    BinTreeNode r = NULL,
    BinTreeNode p = NULL,
    RB_TREE_COLOR c = RED ):data(v), left(l), right(r), parent(p), color(c) {}
};

class RedBlackTree {
public:
  RedBlackTree():root(NULL) {
    nil = new TNode(0, NULL, NULL, NULL, BLACK);
  }
  void insert(int);
  void remove(BinTreeNode);
  BinTreeNode search(int);
private:
  BinTreeNode root;
  BinTreeNode nil;
  void rb_insert_fixup(BinTreeNode);
  void rb_remove_fixup(BinTreeNode);
  void left_rotate(BinTreeNode);
  void right_rotate(BinTreeNode);
  void rb_transplant(BinTreeNode, BinTreeNode);
  BinTreeNode tree_minimum(BinTreeNode);
};

#endif // __RED_BLACK_H
