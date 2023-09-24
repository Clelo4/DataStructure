#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__
#include <stdlib.h>
#include "BinarySearchTree.h"

/**
 * AVL树，左右子树的高度差不超过1
 */
class AVLTree : public BinarySearchTree {
public:
  void insert_node(Node *);
  void delete_node(Node *);
};

#endif // __AVL_TREE_H__