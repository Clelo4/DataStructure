//
// Created by jack on 2021/12/4.
//

#include <stdio.h>
#include "RedBlackTree.h"

#define TRANSPLANT(T, u, v)                                                                                            \
  {                                                                                                                    \
    if (u->parent == nil)                                                                                              \
      T->root = v;                                                                                                     \
    else if (u == u->parent->left)                                                                                     \
      u->parent->left = v;                                                                                             \
    else                                                                                                               \
      u->parent->right = v;                                                                                            \
    v->parent = u->parent;                                                                                             \
  }

Node *RedBlackTree::search_key(int key) {
  Node *x = this->root;
  while (x != nil && x->key != key) {
    if (key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  return x;
}

void RedBlackTree::insert_node(Node *z) {
  if (z == nil)
    return;
  int key = z->key;
  Node *x_p = nil;
  Node *x = this->root;
  while (x != nil) {
    x_p = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->parent = x_p;
  if (x_p == nil) {
    this->root = z;
  } else if (z->key < x_p->key) {
    x_p->left = z;
  } else {
    x_p->right = z;
  }
  z->left = z->right = nil;
  z->color = RED;
  rb_insert_fixup(z);
}

void RedBlackTree::delete_node(Node *target) {
  if (target == NULL || target == nil)
    return;
  Node *y = target;
  Node *replace_target = nil;
  RB_TREE_COLOR original_color = target->color;
  if (target->left == nil) {
    replace_target = target->right;
    TRANSPLANT(this, target, replace_target)
  } else if (target->right == nil) {
    replace_target = target->left;
    TRANSPLANT(this, target, replace_target)
  } else {
    y = tree_minimum(target->right);
    original_color = y->color;
    replace_target = y->right;
    if (target == y->parent) {
      replace_target->parent = y;
    } else {
      TRANSPLANT(this, y, replace_target);
      y->right = target->right;
      y->right->parent = y;
    }
    TRANSPLANT(this, target, y);
    y->left = target->left;
    y->left->parent = y;
    y->color = target->color;
  }
  if (original_color == BLACK)
    rb_remove_fixup(replace_target);
}

void RedBlackTree::rb_insert_fixup(Node *z) {
  while (z->parent->color == RED) {
    if (z->parent->parent->left == z->parent) {
      Node *uncle = z->parent->parent->right;
      if (uncle->color == RED) {
        uncle->color = BLACK;
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z->parent->right == z) {
          z = z->parent;
          left_rotate(z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        right_rotate(z->parent->parent);
      }
    } else {
      Node *uncle = z->parent->parent->left;
      if (uncle->color == RED) {
        uncle->color = BLACK;
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z->parent->left == z) {
          z = z->parent;
          right_rotate(z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        left_rotate(z->parent->parent);
      }
    }
  }
  root->color = BLACK;
}

void RedBlackTree::rb_remove_fixup(Node *x) {
  while (x != root && x->color != RED) {
    if (x == x->parent->left) {
      Node *brother = x->parent->right;
      if (brother->color == RED) {
        brother->color = BLACK;
        x->parent->color = RED;
        left_rotate(x->parent);
        brother = x->parent->right;
      }
      if (brother->left->color == BLACK && brother->right->color == BLACK) {
        brother->color = RED;
        x = x->parent;
      } else {
        if (brother->right->color == BLACK) {
          brother->left->color = BLACK;
          brother->color = RED;
          right_rotate(brother);
          brother = x->parent->right;
        }
        brother->color = x->parent->color;
        x->parent->color = BLACK;
        brother->right->color = BLACK;
        left_rotate(x->parent);
        x = root; // 停止条件
      }
    } else {
      Node *brother = x->parent->left;
      if (brother->color == RED) {
        brother->color = BLACK;
        x->parent->color = RED;
        right_rotate(x->parent);
        brother = x->parent->left;
      }
      if (brother->left->color == BLACK && brother->right->color == BLACK) {
        brother->color = RED;
        x = x->parent;
      } else {
        if (brother->left->color == BLACK) {
          brother->right->color = BLACK;
          brother->color = RED;
          left_rotate(brother);
          brother = x->parent->left;
        }
        brother->color = x->parent->color;
        x->parent->color = BLACK;
        brother->left->color = BLACK;
        right_rotate(x->parent);
        x = root; // 终止条件
      }
    }
  }
  x->color = BLACK;
}

void RedBlackTree::left_rotate(Node *x) {
  Node *y = x->right;
  x->right = y->left;
  if (y->left != nil)
    y->left->parent = x;
  y->parent = x->parent;
  if (x->parent == nil) {
    root = y;
  } else if (x->parent->left == x)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}

void RedBlackTree::right_rotate(Node *x) {
  Node *y = x->left;
  x->left = y->right;
  if (y->right != nil)
    x->left->parent = x;
  y->parent = x->parent;
  if (x->parent == nil) {
    root = y;
  } else if (x->parent->left == x)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->right = x;
  x->parent = y;
}

void RedBlackTree::__pre_order_traversal_recure(Node *t) {
  if (t == nil)
    return;
  printf("%d_%d ", t->key, t->color);
  __pre_order_traversal_recure(t->left);
  __pre_order_traversal_recure(t->right);
}

void RedBlackTree::__in_order_traversal(Node *t) {
  if (t == nil)
    return;
  __in_order_traversal(t->left);
  printf("%d ", t->key);
  __in_order_traversal(t->right);
}

void RedBlackTree::__post_order_traversal(Node *t) {
  if (t == nil)
    return;
  __post_order_traversal(t->left);
  __post_order_traversal(t->right);
  printf("%d ", t->key);
}

int RedBlackTree::__binary_tree_height(Node *t) {
  if (t == nil)
    return 0;
  int left_hight = __binary_tree_height(t->left);
  int right_hight = __binary_tree_height(t->right);
  return (left_hight > right_hight) ? (left_hight + 1) : (right_hight + 1);
}
