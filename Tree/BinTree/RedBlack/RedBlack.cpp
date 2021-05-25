#include "redBlack.h"
#include <stdlib.h>
#include <stdio.h>

BinTreeNode RedBlackTree::search(int val) {
  BinTreeNode target = root;
  while (target != nil) {
    if (target->data == val) {
      return target;
    } else if (target->data < val) {
      target = target->left;
    } else {
      target = target->right;
    }
  }
  return NULL;
};

void RedBlackTree::insert(int val) {  
  BinTreeNode target = root;
  BinTreeNode pre = nil;
  while (target != nil) {
    pre = target;
    if (target->data == val) {
      return;
    } else if (target->data < val) {
      target = target->left;
    } else {
      target = target->right;
    }
  }
  BinTreeNode new_node = new TNode(val);
  new_node->parent = pre;
  if (pre == nil) {
    root = new_node;
    root->parent = nil;
  } else if (val < pre->data) {
    pre->left = new_node;
  } else {
    pre->right = new_node;
  }
  new_node->left = new_node->right = nil;
  new_node->color = RED;
  rb_insert_fixup(new_node);
}

void RedBlackTree::remove(BinTreeNode z) {
  BinTreeNode target = z;
  BinTreeNode replace_target = NULL;
  RB_TREE_COLOR original_color = target->color;
  if (z->left == nil) {
    replace_target = z->right;
    rb_transplant(z, z->right);
  } else if (z->right == nil) {
    replace_target = z->left;
    rb_transplant(z, z->left);
  } else {
    target = tree_minimum(z->right);
    replace_target = target->right;
    if (target->parent == z) {
      replace_target->parent = target;
    } else {
      rb_transplant(target, replace_target);
      target->right = z->right;
      target->right->parent = target;
    }
    rb_transplant(z, target);
    target->left = z->left;
    target->left->parent = target;
    target->color = z->color;
  }

  if (original_color == BLACK) rb_remove_fixup(replace_target);
}

void RedBlackTree::rb_insert_fixup(BinTreeNode z) {
  while (z->parent->color == RED) {
    if (z->parent->parent->left == z->parent) {
      BinTreeNode uncle = z->parent->parent->right;
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
      BinTreeNode uncle = z->parent->parent->left;
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

void RedBlackTree::rb_remove_fixup(BinTreeNode x) {
  while (x != root && x->color != RED) {
    if (x == x->parent->left) {
      BinTreeNode brother = x->parent->right;
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
      BinTreeNode brother = x->parent->left;
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

void RedBlackTree::left_rotate(BinTreeNode x) {
  BinTreeNode p = x->parent;
  BinTreeNode right = x->right;
  x->right = right->left;
  x->right->parent = x;
  right->left = x;
  x->parent = right;
  right->parent = p;
  if (p->left == x) p->left = right;
  else p->right = right;
}

void RedBlackTree::right_rotate(BinTreeNode x) {
  BinTreeNode p = x->parent;
  BinTreeNode left = x->left;
  x->left = left->right;
  x->left->parent = x;
  left->right = x;
  x->parent = left;
  left->parent = p;
  if (p->left == x) p->left = left;
  else p->right = left;
}

void RedBlackTree::rb_transplant(BinTreeNode u, BinTreeNode v) {
  if (u->parent == nil) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

BinTreeNode RedBlackTree::tree_minimum(BinTreeNode x) {
  if (x == nil) return x;
  while (x->left != nil) {
    x = x->left;
  }
  return x;
}
