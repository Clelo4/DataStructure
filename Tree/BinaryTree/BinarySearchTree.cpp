#include "BinarySearchTree.h"

#define TRANSPLANT(T, u, v) { \
  if (u->parent == NULL) T->root = v; \
  else if (u == u->parent->left) u->parent->left = v; \
  else u->parent->right = v; \
  if (v != NULL) v->parent = u->parent; \
}

Node *BinarySearchTree::tree_minimum(Node *x) {
  if (x == NULL) return NULL;
  while (x->left != NULL) x = x->left;
  return x;
}

Node *BinarySearchTree::tree_maxmum(Node *x) {
  if (x == NULL) return NULL;
  while (x->right != NULL) x = x->right;
  return x;
}

void BinarySearchTree::insert_node(Node *z) {
  if (z == NULL) return;
  Node *y = NULL;
  Node *x = this->root;
  while (x != NULL) {
    y = x;
    if (z->key < x->key) x = x->left;
    else x = x->right; 
  }
  z->parent = y;
  if (y == NULL) this->root = z;
  else if (z->key < y->key) y->left = z;
  else y->right = z;
}

Node *BinarySearchTree::search_key(int key) {
  Node *x = this->root;
  while (x != NULL && x->key != key) {
    if (key < x->key) x = x->left;
    else x = x->right;
  }
  return x;
}

void BinarySearchTree::delete_node(Node *z) {
  if (z == NULL) return;
  Node *r = z->right;
  Node *l = z->left;
  if (l == NULL) {
    TRANSPLANT(this, z, r);
  }
  else if (z->right == NULL) {
    TRANSPLANT(this, z, l);
  }
  else {
    Node *y = tree_minimum(r);
    if (z->right != y) {
      Node *yr = y->right;
      TRANSPLANT(this, y, yr);
      y->right = z->right;    
      z->right->parent = y;
    }
    TRANSPLANT(this, z, y);
    y->left = z->left;
    y->left->parent = y;
  }
}

Node* BinarySearchTree::find_min() {
  if (this->root == NULL) return NULL;
  return tree_minimum(this->root);
}
Node* BinarySearchTree::find_max() {
  if (this->root == NULL) return NULL;
  return tree_maxmum(this->root);
}