#include "binTreeSearch.h"

Position TREE_MINIMUM(Position x) {
  while (x->left != NULL) x = x->left;
  return x;
}

Position TREE_MAXMUM(Position x) {
  while (x->right != NULL) x = x->right;
  return x;
}

#define TRANSPLANT(T, u, v) { \
  if (u->parent == NULL) T->root = v; \
  else if (u == u->parent->left) u->parent->left = v; \
  else u->parent->right = v; \
  if (v != NULL) v->parent = u->parent; \
}

void binTreeSearch_insert(BinSearchTree T, Position z) {
  if (T == NULL || z == NULL) return;
  Position y = NULL;
  Position x = T->root;
  while (x != NULL) {
    y = x;
    if (z->key < x->key) x = x->left;
    else x = x->right; 
  }
  z->parent = y;
  if (y == NULL) T->root = z;
  else if (z->key < y->key) y->left = z;
  else y->right = z;
}

Position binTreeSearch_search(BinSearchTree T, int key) {
  if (T == NULL) return NULL;
  Position x = T->root;
  while (x != NULL && x->key != key) {
    if (key < x->key) x = x->left;
    else x = x->right;
  }
  return x;
}

void binTreeSearch_delete(BinSearchTree T, Position z) {
  if (T == NULL || z == NULL) return;
  Position r = z->right;
  Position l = z->left;
  if (z->left == NULL) {
    TRANSPLANT(T, z, r);
  }
  else if (z->right == NULL) {
    TRANSPLANT(T, z, l);
  }
  else {
    Position y = TREE_MINIMUM(r);
    if (z->right != y) {
      Position yr = y->right;
      TRANSPLANT(T, y, yr);
      y->right = z->right;    
      z->right->parent = y;
    }
    TRANSPLANT(T, z, y);
    y->left = z->left;
    y->right = z->right;
  }
}

Position binTreeSearch_find_min(BinSearchTree T) {
  if (T == NULL || T->root == NULL) return NULL;
  return TREE_MINIMUM(T->root);
}
Position binTreeSearch_find_max(BinSearchTree T) {
  if (T == NULL || T->root == NULL) return NULL;
  return TREE_MAXMUM(T->root);
}