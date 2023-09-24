#ifndef __SPLAY_TREE_H__
#define __SPLAY_TREE_H__
#include <stdlib.h>
#include "BinarySearchTree.h"

// SplayTree是自平衡的二叉查找树
// 每次操作（查找、删除、插入）都会将最近访问的结点旋转到定点上
// 最近访问的数据放置的顶层，有利加快下次访问
class SplayTree : public BinarySearchTree {
public:
  Node *search_key(int);
  void insert_node(Node *);
  void delete_node(Node *);

private:
  void _splay(Node *);
};

#endif // __SPLAY_TREE_H__