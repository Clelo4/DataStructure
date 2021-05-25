#include "binTreeSearch.h"

BinTree binTreeSearch_insert(BinTree root, int data) {
  if (!root) {
    return NULL;
  }
  BinTree target = root;
  BinTree newTree = calloc(1, sizeof(struct TNode));
  newTree->data = data;
  while (target)
  {
    if (data <= target->data) {
      if (!target->left) {
        target->left = newTree;
        break;
      }
      target = target->left;
    } else {
      if (!target->right) {
        target->right = newTree;
        break;
      }
      target = target->right;
    }
  }
  return newTree;
}
BinTree binTreeSearch_search(BinTree root, int data) {
  if (!root) {
    return NULL;
  }
  BinTree result = NULL;
  BinTree target = root;
  while (target) {
    if (target->data == data) {
      result = target;
      break;
    } else if (data < target->data) {
      target = target->left;
    } else {
      target = target->right;
    }
  }
  return result;
}
// 1: left, 2: right
void delete_bin_tree(BinTree root, BinTree target, int direct) {
  if (!target) return;
  BinTree replacer_target = NULL;
  if (target->left) {
    // 寻找左子树最大的节点
    BinTree parent = target;
    BinTree parent_direct = 1;
    replacer_target = target->left;
    while (replacer_target->right) {
      parent = replacer_target;
      replacer_target = replacer_target->right;
      parent_direct = 2;
    }
    delete_bin_tree(parent, replacer_target, parent_direct);
  } else if (target->right) {
    // 寻找右子树最小的节点
    BinTree parent = target;
    BinTree parent_direct = 2;
    replacer_target = target->right;
    while (replacer_target->left) {
      parent = replacer_target;
      replacer_target = replacer_target->left;
      parent_direct = 1;
    }
    delete_bin_tree(parent, replacer_target, parent_direct);
  } else {
    // 不寻找替代者
  }
  switch (direct)
  {
  case 1:
    root->left = replacer_target;
    break;
  case 2:
    root->right = replacer_target;
    break;
  default:
    break;
  }
  return;
}

void binTreeSearch_delete(BinTree root, int data) {
  BinTree result = NULL; // 被删除目标
  BinTree target = root;
  BinTree result_parent = NULL; // 被删除目标的父亲
  int direct = 0; // 1: left, 2: right
  while (target) {
    if (target->data == data) {
      result = target;
      break;
    } else if (data < target->data) {
      result_parent = target;
      direct = 1;
      target = target->left;
    } else {
      result_parent = target;
      direct = 2;
      target = target->right;
    }
  }

  if (!result) {
    return;
  }
  delete_bin_tree(result_parent, result, direct);
  free(result);
  return;
}

BinTree binTreeSearch_find_min(BinTree root) {
  BinTree target = root;
  BinTree parent = NULL;
  while (target) {
    parent = target;
    target = target->left;
  }
  return parent;
}
BinTree binTreeSearch_find_max(BinTree root) {
  BinTree target = root;
  BinTree parent = NULL;
  while (target) {
    parent = target;
    target = target->right;
  }
  return parent;
}

