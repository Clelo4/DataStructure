#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

BinTree avl_search(BinTree root, int x) {
  if (!root) return NULL;
  BinTree target = root;
  while (target) {
    if (target->data == x) {
      break;
    } else if (x < target->data) {
      target = target->left;
    } else {
      target = target->right;
    }
  }
  return target;
}
// 计算节点高度
int tree_level(BinTree parent) {
  int left_level = 0;
  int right_level = 0;
  if (parent->left) {
    left_level = parent->left->level;
  }
  if (parent->right) {
    right_level = parent->right->level;
  }
  return (left_level > right_level) ? (left_level + 1) : (right_level + 1);
}
int checkBalance(BinTree parent) {
  int left_level = (parent->left) ? parent->left->level : 0;
  int right_level = (parent->right) ? parent->right->level : 0;

  if (left_level > right_level) {
    if ((left_level - right_level) > 1) {
      return 0;
    } else {
      return 1;
    }
  } else {
    if ((right_level- left_level) > 1) {
      return 0;
    } else {
      return 1;
    }
  }
}

// 重建树结构
BinTree rorate(BinTree l, BinTree p, BinTree r, BinTree A, BinTree B, BinTree C, BinTree D) {
  l->left = A;
  l->right = B;
  l->parent = p;
  if (A) A->parent = l;
  if (B) B->parent = l;
  l->level = tree_level(l);

  r->left = C;
  r->right = D;
  r->parent = p;
  if (C) C->parent = r;
  if (D) D->parent = r;
  r->level = tree_level(r);
  
  p->left = l;
  p->right = r;
  // 重新计算树高度
  p->level = tree_level(p);

  return p;
}

BinTree rebuild(BinTree grandFather, BinTree father, BinTree son) {
  BinTree gGrandFather = grandFather->parent;
  BinTree newRoot = NULL;
  if (grandFather->left == father) {
    if (father->left == son) {
      newRoot = rorate(son, father, grandFather, son->left, son->right, father->right, grandFather->right);
    } else {
      newRoot = rorate(father, son, grandFather, father->left, son->left, son->right, grandFather->right);
    }
  } else {
    if (father->left == son) {
      newRoot = rorate(grandFather, son, father, grandFather->left, son->left, son->right, father->right);
    } else {
      newRoot = rorate(grandFather, father, son, grandFather->left, father->left, son->left, son->right);
    }
  }
  newRoot->parent = gGrandFather;
  if (gGrandFather) {
    (gGrandFather->left == grandFather) ? (gGrandFather->left = newRoot) : (gGrandFather->right = newRoot);
  }
  return newRoot;
}

// 插入新节点。插入操作只会引起一次重建树结构操作
BinTree avl_insert(BinTree root, int x) {
  BinTree insert_tree = calloc(1, sizeof(struct TNode));
  insert_tree->data = x;
  insert_tree->left = insert_tree->right = insert_tree->parent = NULL;
  insert_tree->level = tree_level(insert_tree);
  if (!root) {
    return insert_tree; // new root
  }
  
  BinTree target = root;
  while(target) {
    if (x <= target->data) {
      if (target->left) {
        target = target->left;
      } else {
        target->left = insert_tree;
        insert_tree->parent = target;
        break;
      }
    } else {
      if (target->right) {
        target = target->right;
      } else {
        target->right = insert_tree;
        insert_tree->parent = target;
        break;
      }
    }
  }
  // 从insert_tree的parent开始调整平衡，插入操作只会引起一次平衡调整
  BinTree son, father, grandFather = NULL;
  son = insert_tree;
  father = insert_tree->parent;
  grandFather = (father) ? father->parent : NULL;

  if (father) father->level = tree_level(father);

  while (grandFather) {
    // 检测grandFather的高度
    int old_grandFather_level = grandFather->level;
    grandFather->level = tree_level(grandFather);
    if (grandFather->level == old_grandFather_level) {
      break;
    } else if (checkBalance(grandFather)) {
      // 向上查找
      son = father;
      father = grandFather;
      grandFather = grandFather->parent;
    } else {
      // grandFather失去平衡，进行平衡调整
      BinTree newRoot = rebuild(grandFather, father, son);
      if (!newRoot->parent) return newRoot;
      break;
    }
  }
  // 返回新树的root
  return root;
}

BinTree getBigSon(BinTree parent) {
  if (!parent->left) {
    return parent->right;
  } else if (!parent->right) {
    return parent->left;
  } else if (parent->left->level > parent->right->level){
    return parent->left;
  } else {
    return parent->right;
  }
}

// 删除操作
BinTree avl_delete(BinTree root, int x) {
  // 查找被删除元素
  BinTree target = root;
  while (target) {
    if (x == target->data) {
      break;
    } else if (x < target->data) {
      target = target->left;
    } else {
      target = target->right;
    }
  }
  if (!target) return root;

  BinTree replacer = target; // 替代节点
  BinTree deleter = target; // 临时删除节点
  BinTree tmp = NULL; // 临时填充节点
  BinTree newRoot = root; // 更新后的根节点
  // 查找真正的替代元素节点（没有孩子的节点）
  while (replacer->left || replacer->right) {
    // 在左子树中查找替代者
    if (replacer->left) {
      replacer = replacer->left;
      while (replacer->right) {
        replacer = replacer->right;
      }
    }
    // 在右子树查找替代者
    else {
      replacer = replacer->right;
      while (replacer->left) {
        replacer = replacer->left;
      }
    }
    tmp = calloc(1, sizeof (struct TNode)); // 临时填充节点
    tmp->left = tmp->right = tmp->parent = NULL;
    // 建立临时填充节点
    tmp->parent = replacer->parent;
    tmp->left = replacer->left; if (replacer->left) tmp->left->parent = tmp;
    tmp->right = replacer->right; if (replacer->right) tmp->right->parent = tmp;
    if (replacer->parent) {
      (replacer->parent->left == replacer) ? (replacer->parent->left = tmp) : (replacer->parent->right = tmp);
      replacer->parent = NULL; replacer->left = replacer->right = NULL;
    }
    // 将deleter替换成replacer
    replacer->left = deleter->left; (deleter->left) ? (deleter->left->parent = replacer): NULL;
    replacer->right = deleter->right; (deleter->right) ? (deleter->right->parent = replacer) : NULL;
    replacer->parent = deleter->parent;
    if (deleter->parent) {
      if (deleter->parent->left == deleter) deleter->parent->left = replacer;
      else deleter->parent->right = replacer;
    } else { // 如果realDeleter为根节点，则需要根系整棵树的根节点
      newRoot = replacer;
    }
    free(deleter);
    // 开始新的循环
    deleter = replacer = tmp;
  }

  if (!deleter->parent) { // 为根节点
    free(deleter);
    return NULL;
  }
  if (deleter->parent->left == deleter) {
    deleter->parent->left = NULL;
  }
  else {
    deleter->parent->right = NULL;
  }

  target = deleter->parent;
  free(deleter);

  BinTree son, father, grandFather, gGrandFather = NULL;

  while (target) {
    int old_level = target->level;
    target->level = tree_level(target);
    if (checkBalance(target)) {
      if (old_level == target->level) {
        break;
      } else {
        target = target->parent;
      }
    } else {
      // 调整平衡
      grandFather = target;
      father = getBigSon(grandFather);
      son = getBigSon(father);
      BinTree t = rebuild(grandFather, father, son);
      if (!t->parent) {
        newRoot = t; // 更新整棵树的新节点
      } else {
        target = t->parent;
      }
    }
  }

  return newRoot;
}

BinTree miniNode(BinTree root) {
  BinTree target = root;
  while (target->left) {
    target = target->left;
  }
  return target;
}
int height(BinTree root) {
  if (!root) return 0;
  int left_height = root->left ? root->left->level : 0;
  int right_height = root->right ? root->right->level: 0;
  return left_height > right_height ? (left_height + 1) : (right_height + 1);
}
int max(int a, int b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
}
BinTree leftRorate(BinTree root) {
  BinTree newRoot = root->right;
  BinTree T = newRoot->left;
  newRoot->left = root;
  root->right = T;
  // update height
  root->level = max(height(root->left), height(root->right)) + 1;
  newRoot->level = max(height(newRoot->left), height(newRoot->right)) + 1;
  return newRoot;
}
BinTree rightRorate(BinTree root) {
  BinTree newRoot = root->left;
  BinTree T = newRoot->right;
  newRoot->right = root;
  root->left = T;
  // update height
  root->level = max(height(root->left), height(root->right)) + 1;
  newRoot->level = max(height(newRoot->left), height(newRoot->right)) + 1;
  return newRoot;
}

BinTree avl_delete_v2(BinTree root, int x) {
  if (!root) return NULL;
  // 查找x
  if (x < root->data) {
    root->left = avl_delete_v2(root->left, x);
  } else if (x > root->data) {
    root->right = avl_delete_v2(root->right, x);
  } else {
    if (root->left == NULL || root->right == NULL) {
      BinTree temp = root->left ? root->left : root->right;
      free(root);
      if (temp == NULL) {
        root = NULL;
      } else {
        root = temp;
      }
    } else {
      BinTree replacer = miniNode(root->right);
      root->data = replacer->data;
      root->right = avl_delete_v2(root->right, replacer->data);
    }
  }
  // 重新计算高度、调整平衡
  if (!root) return root;
  int isBalance = height(root->left) - height(root->right);

  BinTree son = NULL;
  if (isBalance > 1) {
    son = root->left;
    if (height(son->left) > height(son->right)) {
      root = rightRorate(root);
    } else {
      root->left = leftRorate(son);
      root = rightRorate(root);
    }
  }
  if (isBalance < -1) {
    son = root->right;
    if (height(son->left) > height(son->right)) {
      root->right = rightRorate(son);
      root = leftRorate(root);
    } else {
      root = leftRorate(root);
    }
  }
  return root;
}

BinTree avl_insert_v2(BinTree root, int x) {
  BinTree newNode = calloc(1, sizeof(struct TNode));
  newNode->data = x; newNode->left = newNode->right = NULL; newNode->level = height(newNode);
  if (!root) return newNode;

  if (x <= root->data) {
    if (root->left) {
      root->left = avl_insert_v2(root->left, x);
    } else {
      root->left = newNode;
    }
  } else {
    if (root->right) {
      root->right = avl_insert_v2(root->right, x);
    } else {
      root->right = newNode;
    }
  }

  // update height
  int isBalance = height(root->left) - height(root->right);
  BinTree son = NULL;

  if (isBalance > 1) {
    son = root->left;
    if (height(son->left) > height(son->right)) {
      root = rightRorate(root);
    } else {
      root->left = leftRorate(son);
      root = rightRorate(root);
    }
  }
  if (isBalance < -1) {
    son = root->right;
    if (height(son->left) > height(son->right)) {
      root->right = rightRorate(son);
      root = leftRorate(root);
    } else {
      root = leftRorate(root);
    }
  }

  return root;
}