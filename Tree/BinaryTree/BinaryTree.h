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
    if (u->parent == NULL)                                                                                             \
      T->root = v;                                                                                                     \
    else if (u == u->parent->left)                                                                                     \
      u->parent->left = v;                                                                                             \
    else                                                                                                               \
      u->parent->right = v;                                                                                            \
    if (v != NULL)                                                                                                     \
      v->parent = u->parent;                                                                                           \
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

  // 先序遍历
  void pre_order_traversal();
  // 中序遍历
  void in_order_traversal();
  // 后序遍历
  void post_order_traversal();
  // 层次遍历，从上到下，从左到右
  void level_order_traversal();
  // 求树高度
  int binary_tree_height();
};

#endif /* __BinaryTree_H__ */