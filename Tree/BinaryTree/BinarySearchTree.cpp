#include "BinarySearchTree.h"

void BinarySearchTree::insert_node(Node *z) {
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
}

Node *BinarySearchTree::search_key(int key) {
  Node *x = this->root;
  while (x != NULL && x->key != key) {
    if (key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  return x;
}

void BinarySearchTree::delete_node(Node *z) {
  if (z == NULL)
    return;
  Node *r = z->right;
  Node *l = z->left;
  if (l == NULL) {
    TRANSPLANT(this, z, r);
  } else if (z->right == NULL) {
    TRANSPLANT(this, z, l);
  } else {
    Node *y = TREE_MINIMUM(r);
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

Node *BinarySearchTree::find_min() {
  if (this->root == NULL)
    return NULL;
  return TREE_MINIMUM(this->root);
}
Node *BinarySearchTree::find_max() {
  if (this->root == NULL)
    return NULL;
  return TREE_MAXMUM(this->root);
}