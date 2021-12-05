#include <stdlib.h>
#include <assert.h>
#include "AVLTree.h"

#define IsLChild(x) ((x)->parent->left == x)
#define IsRChild(x) ((x)->parent->right == x)
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

bool _AvlBalanced(Node *x) {
  if (x == NULL)
    return true;
  int left_level = (x->left) ? x->left->level : 0;
  int right_level = (x->right) ? x->right->level : 0;
  return (left_level - right_level) < 2 && (left_level - right_level) > -2;
}

void _updateHeight(Node *x) {
  if (x == NULL)
    return;
  int left_level = (x->left) ? x->left->level : 0;
  int right_level = (x->right) ? x->right->level : 0;
  x->level = ((left_level > right_level) ? left_level : right_level) + 1;
}

Node *_connect34(Node *a, Node *b, Node *c, Node *al, Node *ar, Node *cl, Node *cr) {
  a->left = al;
  a->right = ar;
  if (al)
    al->parent = a;
  if (ar)
    ar->parent = a;
  c->left = cl;
  c->right = cr;
  if (cl)
    cl->parent = c;
  if (cr)
    cr->parent = c;
  _updateHeight(a);
  _updateHeight(b);
  c->parent = a->parent = b;
  b->left = a;
  b->right = c;
  _updateHeight(b);
  return b;
}

Node *_rotateAt(Node *v) {
  if (v == NULL)
    return NULL;
  Node *p = v->parent;
  Node *g = p->parent;
  assert(p != NULL);
  assert(g != NULL);
  if (IsLChild(p)) {
    if (IsLChild(v)) {
      return _connect34(v, p, g, v->left, v->right, p->right, g->right);
    } else {
      return _connect34(p, v, g, p->left, v->left, v->right, g->right);
    }
  } else {
    if (IsLChild(v)) {
      return _connect34(g, v, p, g->left, v->left, p->left, p->right);
    } else {
      return _connect34(g, p, v, g->left, p->left, v->left, v->right);
    }
  }
}

Node *_tallerChild(Node *x) {
  if (x == NULL)
    return NULL;
  int left_level = (x->left) ? x->left->level : 0;
  int right_level = (x->right) ? x->right->level : 0;
  return (left_level > right_level) ? x->left : x->right;
}

void AVLTree::insert_node(Node *z) {
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
  if (y == NULL) {
    this->root = z;
  } else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;
  // 重建树高度
  z->level = 1;
  for (Node *g = y; g; g = g->parent) {
    if (!_AvlBalanced(g)) {
      Node *gp = g->parent;
      Node *n = _rotateAt(_tallerChild(_tallerChild(g)));
      if (n)
        n->parent = gp;
      if (gp) {
        if (gp->left == g)
          gp->left = n;
        else
          gp->right = n;
      } else {
        this->root = n;
      }
      break;
    } else {
      _updateHeight(g);
    }
  }
}

void AVLTree::delete_node(Node *z) {
  if (z == NULL)
    return;
  Node *r = z->right;
  Node *l = z->left;
  Node *_hot = NULL;
  if (l == NULL) {
    TRANSPLANT(this, z, r);
    _hot = z->parent;
  } else if (z->right == NULL) {
    TRANSPLANT(this, z, l);
    _hot = z->parent;
  } else {
    Node *y = tree_minimum(r);
    if (z->right != y) {
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
    y->left->parent = y;
  }
  for (Node *g = _hot; g;) {
    if (!_AvlBalanced(g)) {
      Node *gp = g->parent;
      Node *n = _rotateAt(_tallerChild(_tallerChild(g)));
      if (n)
        n->parent = gp;
      if (gp) {
        if (gp->left == g)
          gp->left = n;
        else
          gp->right = n;
      } else {
        this->root = n;
      }
      g = gp;
    } else {
      _updateHeight(g);
      g = g->parent;
    }
  }
}