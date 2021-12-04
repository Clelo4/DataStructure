#include "redBlack.h"
#include <stdlib.h>
#include <stdio.h>

// 参考：https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/amp/

// 重建树结构
BinTree rorate(BinTree l, BinTree p, BinTree r, BinTree A, BinTree B, BinTree C, BinTree D) {
  l->left = A;
  l->right = B;
  l->parent = p;
  if (A) A->parent = l;
  if (B) B->parent = l;

  r->left = C;
  r->right = D;
  r->parent = p;
  if (C) C->parent = r;
  if (D) D->parent = r;
  
  p->left = l;
  p->right = r;

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

BinTree getUncle(BinTree target) {
    BinTree father = target->parent;
    if (!father) return NULL;
    BinTree grandFather = father->parent;
    if (!grandFather) return NULL;
    if (grandFather->left == father) return grandFather->right;
    else return grandFather->left;
}
BinTree getSibling(BinTree target) {
    BinTree father = target->parent;
    if (!father) return NULL;
    if (father->left == target) return father->right;
    else return father->left;
}

void solveDoubleRed(BinTree target) {
    if (!target->parent) {
        // 将树根染为黑色
        target->color = BLACK;
        return;
    }
    BinTree father = target->parent;
    if (father->color == BLACK) return; // 若father为黑，则返回
    BinTree grandFather = father->parent; // 因为father为红，则grandFather必然存在，且必为黑
    BinTree uncle = getUncle(target);
    if (!uncle || uncle->color == BLACK) { // 如果uncle为黑或NULL
        grandFather->color = RED; // grandFather必然染为红色
        BinTree gg = grandFather->parent;
        BinTree newRoot = rebuild(grandFather, father, target);
        newRoot->color = BLACK; // 新祖父节点染为黑色
        // 重新将newRoot与gg建立联系
        newRoot->parent = gg;
        if (gg) {
            (gg->left == grandFather) ? (gg->left = newRoot) : (gg->right = newRoot);
        }
    } else { // 如果uncle为红，可能会导致再次双红修改
        // 将grandFather染为红色，将其两个孩子染为黑色
        grandFather->color = RED;
        grandFather->left->color = grandFather->right->color = BLACK;
        solveDoubleRed(grandFather);
    }
}
void solveDoubleBlack(BinTree target) {
    if (!target->parent) return;

    BinTree sibling = getSibling(target), father = target->parent;
    if (sibling == NULL) {
        solveDoubleBlack(target->parent);
    } else {
        if (sibling->color == RED) {
            BinTree newRoot = NULL;
            BinTree gg = target->parent->parent;
            free(target);
            if (sibling->parent->left == sibling) {
                sibling->parent->right = NULL;
                newRoot = rebuild(sibling->parent, sibling, sibling->left);
                newRoot->color = BLACK;
                newRoot->right->color = BLACK;
                newRoot->right->left->color = RED;
            } else {
                sibling->parent->left = NULL;
                newRoot = rebuild(sibling->parent, sibling, sibling->right);
                newRoot->color = BLACK;
                newRoot->left->color = BLACK;
                newRoot->left->right->color = RED;
            }
            newRoot->parent = gg;
            if (gg) {
                if (gg->left == father) gg->left = newRoot;
                else gg->right = newRoot;
            }
        } else if ((!sibling->left && !sibling->right) || (sibling->left->color == BLACK && sibling->right->color == BLACK)) {
            free(target);
            sibling->color = RED;
            if (father->color == RED) {
                father->color = BLACK;
            }
            else {
                solveDoubleBlack(father);
            }
        } else {
            BinTree son = NULL;
            if (father->left == sibling) {
                if (sibling->left) son = sibling->left;
                else son = sibling->right;
            } else {
                if (sibling->right) son = sibling->right;
                else son = sibling->left;
            }
            BinTree gg = target->parent->parent;
            BinTree newRoot = rebuild(father, sibling, son);
            if (newRoot->left) newRoot->left->color = BLACK;
            if (newRoot->right) newRoot->right->color = BLACK;
            
            newRoot->parent = gg;
            if (gg) {
                if (gg->left == father) gg->left = newRoot;
                else gg->right = newRoot;
            }
        }
    }

}
int updateHeight(BinTree);

BinTree red_black_insert(BinTree root, int x) {
    BinTree grandFather = NULL;
    BinTree newNode = calloc(1, sizeof(struct TNode));
    newNode->data = x;
    newNode->left = newNode->right = newNode->parent = NULL;
    if (!root) {
        newNode->color = BLACK; // 颜色：BLACK为黑色，RED为红色
        return newNode;
    }
    BinTree target = root;
    while (target) {
        if (x <= target->data) {
            if (target->left) {
                target = target->left;
            } else {
                target->left = newNode;
                break;
            }
        } else {
            if (target->right) {
                target = target->right;
            } else {
                target->right = newNode;
                break;
            }
        }
    }
    newNode->color = RED; // 颜色：BLACK为黑色，RED为红色
    newNode->parent = target;
    solveDoubleRed(newNode);
    return newNode;
}
void red_black_delete(BinTree root, int x) {
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
    if (!target) {
        // 没有找到目标节点
        return;
    }

    // 查找替代节点
    BinTree deleter, replacer, tmp;
    deleter = replacer = target;
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

        tmp = calloc(1, sizeof(struct TNode));
        tmp->color = replacer->color;
        tmp->left = replacer->left; if (tmp->left) tmp->left->parent = tmp;
        tmp->right = replacer->right; if (tmp->right) tmp->right->parent = tmp;
        tmp->parent = replacer->parent;
        if (replacer->parent) (replacer->parent->left == replacer) ? (tmp->parent->left = tmp) : (tmp->parent->right = tmp);
        // 将deleter替换成replacer
        replacer->color = deleter->color;
        replacer->left = deleter->left; if (deleter->left) deleter->left->parent = replacer;
        replacer->right = deleter->right; if (deleter->right) deleter->right->parent = replacer;
        replacer->parent = deleter->parent;
        if (deleter->parent) (deleter->parent->left == deleter) ? (replacer->parent->left = replacer) : (replacer->parent->right = replacer);
        free(deleter);
        deleter = replacer = tmp;
    }

    if (!deleter->parent) {
        free(deleter);
        return;
    }

    if (deleter->parent->left == deleter) deleter->parent->left = NULL;
    else deleter->parent->right = NULL;

    if (deleter->color == RED) { // deleter为红色，直接删除
        free(deleter);
    } else {
        solveDoubleBlack(deleter);
    }
}