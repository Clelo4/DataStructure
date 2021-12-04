#include <stack>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

void _delete_binary_tree(Node *root) {
  if (root == NULL)
    return;
  _delete_binary_tree(root->left);
  _delete_binary_tree(root->right);
  free(root);
}

BinaryTree::~BinaryTree() { _delete_binary_tree(root); }

// 递归实现
void __pre_order_traversal_recure(Node *root) {
  if (root == NULL)
    return;
  printf("%d ", root->key);
  __pre_order_traversal_recure(root->left);
  __pre_order_traversal_recure(root->right);
}
void __in_order_traversal_recure(Node *root) {
  if (root == NULL)
    return;
  __in_order_traversal_recure(root->left);
  printf("%d ", root->key);
  __in_order_traversal_recure(root->right);
}
void __post_order_traversal_recure(Node *root) {
  if (root == NULL)
    return;
  __post_order_traversal_recure(root->left);
  __post_order_traversal_recure(root->right);
  printf("%d ", root->key);
}

int __tree_hight_recure(Node *root) {
  if (root == NULL)
    return 0;
  int left_hight = __tree_hight_recure(root->left);
  int right_hight = __tree_hight_recure(root->right);
  return (left_hight > right_hight) ? (left_hight + 1) : (right_hight + 1);
}

// 迭代实现，使用堆栈实现
void __pre_order_traversal_iterate(Node *root) {
  if (root == NULL)
    return;
  std::stack<Node *> s;
  Node *target = root;
  s.push(target);
  while (!s.empty()) {
    target = s.top();
    s.pop();
    printf("%d ", target->key);
    if (target->right)
      s.push(target->right);
    if (target->left)
      s.push(target->left);
  }
}
void __in_order_traversal_iterate(Node *root) {
  if (root == NULL)
    return;
  std::stack<Node *> s;
  Node *target = root;
  while (1) {
    while (target) {
      s.push(target);
      target = target->left;
    }
    if (!s.empty()) {
      Node *parent = s.top();
      s.pop();
      printf("%d ", parent->key);
      target = parent->right;
    } else {
      break;
    }
  }
}
void __post_order_traversal_iterate(Node *root) {
  if (root == NULL)
    return;
  std::stack<Node *> s;
  Node *target = root;
  Node *pre = NULL;
  while (1) {
    while (target) {
      s.push(target);
      target = target->left;
    }
    if (s.empty())
      break;
    Node *current = s.top();
    if (current->right == NULL || pre == current->right) {
      pre = current;
      s.pop();
      printf("%d ", pre->key);
    } else if (current->right)
      target = current->right;
  }
}

void BinaryTree::level_order_traversal() {
  if (this->root == NULL)
    return;
  std::queue<Node *> q;
  q.push(this->root);
  while (!q.empty()) {
    Node *target = q.front();
    q.pop();
    if (target->left) {
      q.push(target->left);
    }
    if (target->right) {
      q.push(target->right);
    }
    // print
    printf("%d ", target->key);
  }
  return;
}

void BinaryTree::pre_order_traversal() {
#ifdef USE_TRAVERSAL_ITERATE
  __pre_order_traversal_iterate(this->root);
#else
  __pre_order_traversal_recure(this->root);
#endif
}

void BinaryTree::in_order_traversal() {
#ifdef USE_TRAVERSAL_ITERATE
  __in_order_traversal_iterate(this->root);
#else
  __in_order_traversal_recure(this->root);
#endif
}

void BinaryTree::post_order_traversal() {
#ifdef USE_TRAVERSAL_ITERATE
  __post_order_traversal_iterate(this->root);
#else
  __post_order_traversal_recure(this->root);
#endif
}

int BinaryTree::binary_tree_height() { return __tree_hight_recure(this->root); }
