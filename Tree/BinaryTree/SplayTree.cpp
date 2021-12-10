#include <stdlib.h>
#include <assert.h>
#include "SplayTree.h"

#define LEFT_ROTATE(p)                                                                                                 \
  {                                                                                                                    \
    Node *pp = p->parent;                                                                                              \
    Node *right_child = p->right;                                                                                      \
    p->right = right_child->left;                                                                                      \
    if (p->right)                                                                                                      \
      p->right->parent = p;                                                                                            \
    right_child->left = p;                                                                                             \
    p->parent = right_child;                                                                                           \
    right_child->parent = pp;                                                                                          \
    if (pp) {                                                                                                          \
      if (pp->left == p)                                                                                               \
        pp->left = right_child;                                                                                        \
      else                                                                                                             \
        pp->right = right_child;                                                                                       \
    }                                                                                                                  \
  }

#define RIGHT_ROTATE(p)                                                                                                \
  {                                                                                                                    \
    Node *pp = p->parent;                                                                                              \
    Node *left_child = p->left;                                                                                        \
    p->left = left_child->right;                                                                                       \
    if (p->left)                                                                                                       \
      p->left->parent = p;                                                                                             \
    left_child->right = p;                                                                                             \
    p->parent = left_child;                                                                                            \
    left_child->parent = pp;                                                                                           \
    if (pp) {                                                                                                          \
      if (pp->left == p)                                                                                               \
        pp->left = left_child;                                                                                         \
      else                                                                                                             \
        pp->right = left_child;                                                                                        \
    }                                                                                                                  \
  }

void SplayTree::_splay(Node *z) {
  if (z == NULL)
    return;
  Node *p, *g;
  // 双层延展循环
  while ((p = z->parent) && (g = p->parent)) {
    Node *r = g->parent;
    if (IsLChild(p)) {
      if (IsLChild(z)) {
        p->left = z->right;
        if (z->right)
          z->right->parent = p;
        z->right = g;
        g->parent = z;
      } else {
        p->right = z->left;
        if (z->left)
          z->left->parent = p;
        z->left = p;
        p->parent = z;
        g->left = z->right;
        if (z->right)
          z->right->parent = g;
        z->right = g;
        g->parent = z;
      }
    } else {
      if (IsLChild(z)) {
        p->left = z->right;
        if (z->right)
          z->right->parent = p;
        z->right = p;
        p->parent = z;
        g->right = z->left;
        if (z->left)
          z->left->parent = g;
        z->left = g;
        g->parent = z;
      } else {
        p->right = z->left;
        if (z->left)
          z->left->parent = p;
        z->left = g;
        g->parent = z;
      }
    }
    z->parent = r;
    if (r) {
      if (g == r->left) {
        r->left = z;
      } else {
        r->right = z;
      }
    }
  }
  // 判断是否需要最后一次的单层延展
  if ((p = z->parent)) {
    if (IsLChild(z)) {
      RIGHT_ROTATE(p);
    } else {
      LEFT_ROTATE(p);
    }
  }
  z->parent = NULL;
  this->root = z;
}

Node *SplayTree::search_key(int key) {
  Node *y = NULL;
  Node *x = this->root;
  while (x != NULL && x->key != key) {
    y = x;
    if (key < x->key)
      x = x->left;
    else if (key > x->key)
      x = x->right;
  }
  _splay((x) ? x : y);
  return x;
}

void SplayTree::insert_node(Node *z) {
  if (z == NULL)
    return;
  Node *y = NULL;
  Node *x = this->root;
  while (x != NULL) {
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->parent = y;
  if (y == NULL)
    this->root = z;
  else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;
  _splay(z);
}

void SplayTree::delete_node(Node *z) {
  if (z == NULL)
    return;
  Node *r = z->right;
  Node *l = z->left;
  Node *_hot = NULL;
  if (z->left == NULL) {
    TRANSPLANT(this, z, r);
    _hot = z->parent;
  } else if (z->right == NULL) {
    TRANSPLANT(this, z, l);
    _hot = z->parent;
  } else {
    Node *y = tree_minimum(r);
    if (z->right != r) {
      _hot = y->parent;
      Node *yr = y->right;
      TRANSPLANT(this, y, yr);
      y->right = z->right;
      z->right->parent = y;
    } else {
      _hot = y;
    }
    TRANSPLANT(this, z, y);
    y->left = z->left;
    z->left->parent = y;
  }
  _splay(_hot);
}
