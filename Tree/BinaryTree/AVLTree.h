#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__
#include <stdlib.h>
#include "BinarySearchTree.h"

class AVLTree : public BinarySearchTree {
public:
  void insert_node(Node *);
  void delete_node(Node *);
};

#endif // __AVL_TREE_H__