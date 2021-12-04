#ifndef __BinarySearchTree_H__
#define __BinarySearchTree_H__

#include <stdio.h>
#include "BinaryTree.h"

class BinarySearchTree : public BinaryTree {
public:
  void insert_node(Node *);
  Node *search_key(int);
  void delete_node(Node *);
  Node *tree_minimum(Node *);
  Node *tree_maxmum(Node *x);
  Node *find_min();
  Node *find_max();
};

#endif // __BinarySearchTree_H__