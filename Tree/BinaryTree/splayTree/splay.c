#include "splay.h"
#include <stdlib.h>
#include <stdio.h>

// error: -1, left: 1, right: 0
int isLeft(BinTree target) {
  if (!target) return -1;
  BinTree father = target->parent;
  if (!father) return -1;
  if (father->left == target) return 1;
  else return 0;
}

// 旋转调整
BinTree rotate(BinTree target) {
  if (!target) return NULL;
  BinTree father = target->parent;
  BinTree grandFather = NULL;
  if (!father) return target;
  grandFather = father->parent;
  if (!grandFather) {
    if (isLeft(target)) {
      target->parent = father->parent;
      father->left = target->right; if(father->left) father->left->parent = father;
      target->right = father; father->parent = target;
    } else {
      target->parent = father->parent;
      father->right = target->left; if(father->right) father->right->parent = father;
      target->left = father; father->parent = target;
    }
  } else {
    if (isLeft(target) == 1 && isLeft(father) == 1) {
      father->left = target->right; if(father->left) father->left->parent = father;
      target->right = grandFather; grandFather->parent = target;
    } else if (isLeft(target) == 1 && isLeft(father) == 0) {
      father->left = target->right; if(father->left) father->left->parent = father;
      grandFather->right = target->left; if (grandFather->right) grandFather->right->parent = grandFather;
      target->left = grandFather; grandFather->parent = target;
      target->right = father; father->parent = target;
    } else if (isLeft(target) == 0 && isLeft(father) == 1) {
      father->right = target->left; if(father->right) father->right->parent = father;
      grandFather->left = target->right; if (grandFather->left) grandFather->left->parent = grandFather;
      target->left = father; father->parent = target;
      target->right = grandFather; grandFather->parent = target;
    }
    else if (isLeft(target) == 0 && isLeft(father) == 0) {
      father->right = target->left; if(father->right) father->right->parent = father;
      target->left = grandFather; grandFather->parent = target;
    }
  }
  return target;
}

BinTree splay_search(BinTree root, int x) {
  BinTree target = root;
  if (!target) return NULL;
  while (target) {
    if (target->data == x) break;
    if (x < target->data) {
      target = target->left;
    } else {
      target = target->right;
    }
  }
  return __splay(target);
}
BinTree splay_insert(BinTree root, int x) {
  BinTree target = root;
  BinTree newNode = calloc(1, sizeof(struct TNode));
  newNode->parent = newNode->left = newNode->right = NULL;
  newNode->data = x;
  if (!target) {
    return newNode;
  }
  while(target) {
    if (x <= target->data) {
      if (target->left) {
        target = target->left;
      } else {
        target->left = newNode;
        newNode->parent = target;
        break;
      }
    } else {
      if (target->right) {
        target = target->right;
      } else {
        target->right = newNode;
        newNode->parent = target;
        break;
      }
    }
  }
  return __splay(newNode);
}
BinTree splay_delete(BinTree root, int x) {
  BinTree target = root;
  BinTree _hot = NULL;
  if (!target) {
    return NULL;
  }
  while (target) {
    if (x == target->data) {
      break;
    } else if (x < target->data) {
      _hot = target;
      target = target->left;
    } else {
      _hot = target;
      target = target->right;
    }
  }
  if (!target) return __splay(_hot);

  BinTree deleter = target, replacer = target;
  BinTree tmp = NULL;
  while (replacer->left || replacer->right) {
    if (replacer->left) {
      replacer = replacer->left;
      while (replacer->right) {
        replacer = replacer->right;
      }
    } else {
      replacer = replacer->right;
      while (replacer->left) {
        replacer = replacer->left;
      }
    }
    // 建立临时填充节点
    tmp = calloc(1, sizeof(struct TNode));
    tmp->parent = replacer->parent;
    tmp->left = replacer->left; if (replacer->left) tmp->left->parent = tmp;
    tmp->right = replacer->right; if (replacer->right) tmp->right->parent = tmp;
    if (replacer->parent) {
      (replacer->parent->left == replacer) ? (replacer->parent->left = tmp) : (replacer->parent->right = tmp);
      replacer->parent = NULL; replacer->left = replacer->right = NULL;
    }
    // 将deleter替换成replacer
    replacer->left = deleter->left; if (deleter->left) deleter->left->parent = replacer;
    replacer->right = deleter->right; if (deleter->right) deleter->right->parent = replacer;
    replacer->parent = deleter->parent;

    if (deleter->parent) {
      if (deleter->parent->left == deleter) {
        deleter->parent->left = replacer;
      } else {
        deleter->parent->right = replacer;
      }
    }
    replacer = deleter = tmp;
  }

  _hot = tmp->parent;
  (_hot->left == tmp) ? (_hot->left = NULL): (_hot->right = NULL);
  free(deleter);
  return __splay(_hot);
}
BinTree __splay(BinTree target) {
  if (!target) return NULL;
  BinTree father, grandFather, gg= NULL;
  while((father = target->parent) && (grandFather = father->parent)) {
    gg = grandFather->parent;
    int t1 = isLeft(grandFather);
    rotate(target);
    target->parent = gg;
    if (gg) {
      switch (t1)
      {
      case 1:
        gg->left = target;
        break;
      case 0:
        gg->right = target;
        break;
      default:
        break;
      }
    }
  }
  rotate(target);
  if (target) { target->parent = NULL; }
  return target;
}

BinTree leftRorate(BinTree root) {
  BinTree newRoot = root->right;
  BinTree T = newRoot->left;
  newRoot->left = root;
  root->right = T;
  return newRoot;
}

BinTree rightRorate(BinTree root) {
  BinTree newRoot = root->left;
  BinTree T = newRoot->right;
  newRoot->right = root;
  root->left = T;
  return newRoot;
}

BinTree twoLevelRightRorate(BinTree splayNode, BinTree root) {
  BinTree T = splayNode->right;
  splayNode->right = root; root->left = T;
  return splayNode;
}

BinTree twoLevelLeftRorate(BinTree splayNode, BinTree root) {
  BinTree T = splayNode->left;
  splayNode->left = root; root->right = T;
  return splayNode;
}
// 双层延展
BinTree splay_v2(BinTree root, int key) {
  if (!root) return NULL;
  if (root == NULL || key == root->data) {
    return root;
  } else if (key < root->data) {
    if (root->left == NULL) {
      return root;
    } else if (root->left->data == key) {
      return rightRorate(root);
    } else if (root->left->data > key) {
      if (root->left->left == NULL) return rightRorate(root);
      BinTree splayNode = splay_v2(root->left->left, key);
      return twoLevelRightRorate(splayNode, root);
    } else {
      if (root->left->right == NULL) return rightRorate(root);
      BinTree splayNode = splay_v2(root->left->right, key);
      splayNode = leftRorate(splayNode)->left;
      return twoLevelRightRorate(splayNode, root);
    }
  } else {
    if (root->right == NULL) {
      return root;
    } else if (root->right->data == key) {
      return leftRorate(root);
    } else if (root->right->data > key) {
      if (root->right->left == NULL) return leftRorate(root);
      BinTree splayNode = splay_v2(root->right->left, key);
      splayNode = rightRorate(splayNode)->right;
      return twoLevelLeftRorate(splayNode, root);
    } else {
      if (root->right->right == NULL) return leftRorate(root);
      BinTree splayNode = splay_v2(root->right->right, key);
      return twoLevelLeftRorate(splayNode, root);
    }
  }
}

BinTree splay_search_v2(BinTree root, int key) {
  return splay_v2(root, key);
}

BinTree splay_insert_v2(BinTree root, int key) {
  BinTree newNode = calloc(1, sizeof(struct TNode));
  newNode->left = newNode->right = NULL; newNode->data = key;

  root = splay_v2(root, key);
  if (!root) return newNode;

  if (key < root->data) {
    newNode->right = root;
    newNode->left = root->left;
    root->left = NULL;
  } else {
    newNode->left = root;
    newNode->right = root->right;
    root->right = NULL;
  }

  return newNode;
}

BinTree splay_delete_v2(BinTree root, int key) {
  if (!root) return root;
  BinTree target = root;
  while (target) {
    if (target->data == key) {
      break;
    } else if (target->data > key) {
      target = target->left;
    } else {
      target = target->right;
    }
  }
  if (target) free(target);

  return root = splay_v2(root, key);;
}
