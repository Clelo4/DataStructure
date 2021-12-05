#ifndef __SPLAY_TREE_H__
#define __SPLAY_TREE_H__
#include <stdlib.h>
#include "BinarySearchTree.h"

class SplayTree : public BinarySearchTree {
public:
  Node *search_key(int);
  void insert_node(Node *);
  void delete_node(Node *);

private:
  void _splay(Node *);
};

#endif // __SPLAY_TREE_H__