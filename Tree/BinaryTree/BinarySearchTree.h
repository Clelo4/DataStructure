#ifndef __BinarySearchTree_H__
#define __BinarySearchTree_H__

#include <stdio.h>
#include "BinaryTree.h"

#define TREE_MINIMUM(x)                                                                                                \
  ({                                                                                                                   \
    auto _x = x;                                                                                                       \
    while (_x && _x->left != NULL)                                                                                     \
      _x = _x->left;                                                                                                   \
    _x;                                                                                                                \
  })
#define TREE_MAXMUM(x)                                                                                                 \
  ({                                                                                                                   \
    auto _x = x;                                                                                                       \
    while (_x && _x->right != NULL)                                                                                    \
      _x = _x->right;                                                                                                  \
    _x;                                                                                                                \
  })

class BinarySearchTree : public BinaryTree {
public:
  void insert_node(Node *);
  Node *search_key(int);
  void delete_node(Node *);
  Node *find_min();
  Node *find_max();
};

#endif // __BinarySearchTree_H__