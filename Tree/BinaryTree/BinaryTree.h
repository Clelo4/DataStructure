//
//  binTree.h
//  data_structure
//
//  Created by jack on 2020/12/10.
//

#ifndef __BinaryTree_H__
#define __BinaryTree_H__

#include <stdlib.h>

#define IsLChild(x)                                                                                                    \
  ({                                                                                                                   \
    auto _x = x;                                                                                                       \
    _x->parent->left == x;                                                                                             \
  })

#define IsRChild(x)                                                                                                    \
  ({                                                                                                                   \
    auto _x = x;                                                                                                       \
    _x->parent->right == _x;                                                                                           \
  })

#define TRANSPLANT(T, u, v)                                                                                            \
  {                                                                                                                    \
    auto _u = u;                                                                                                       \
    auto _v = v;                                                                                                       \
    if (_u->parent == NULL)                                                                                            \
      T->root = _v;                                                                                                    \
    else if (_u == _u->parent->left)                                                                                   \
      _u->parent->left = _v;                                                                                           \
    else                                                                                                               \
      _u->parent->right = _v;                                                                                          \
    if (v != NULL)                                                                                                     \
      _v->parent = _u->parent;                                                                                         \
  }
class Node {
public:
  int key;
  Node *parent;
  Node *left;
  Node *right;
  int level;
  Node(int k) : key(k), parent(NULL), left(NULL), right(NULL), level(1) {}
};

class BinaryTree {
public:
  Node *root;
  BinaryTree() : root(NULL) {
#ifdef DEBUG
#ifdef USE_TRAVERSAL_ITERATE
    printf("DEBUG: USE_TRAVERSAL_ITERATE\n");
#endif
#endif
  }
  ~BinaryTree();

  // ????????????
  void pre_order_traversal();
  // ????????????
  void in_order_traversal();
  // ????????????
  void post_order_traversal();
  // ??????????????????????????????????????????
  void level_order_traversal();
  // ????????????
  int binary_tree_height();
};

#endif /* __BinaryTree_H__ */