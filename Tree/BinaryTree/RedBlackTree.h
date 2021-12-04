//
// Created by jack on 2021/12/4.
//

#ifndef EXEC_REDBLACKTREE_H
#define EXEC_REDBLACKTREE_H

#include <stdlib.h>

// （1）树根为黑色
// （2）外部节点：均为黑色
// （3）其余节点：若为红节点，则只能有黑孩子
// （4）外部节点到根：途中黑节点树木相等

typedef enum RB_TREE_COLOR {
    BLACK,
    RED,
} RB_TREE_COLOR;

class Node {
public:
    int key;
    Node *parent;
    Node *left;
    Node *right;
    RB_TREE_COLOR color;
    Node(int k, RB_TREE_COLOR c = RED):key(k), parent(NULL), left(NULL), right(NULL), color(c) {}
};

class RedBlackTree{
public:
    RedBlackTree() {
        root = nil = new Node(0, BLACK);
        nil->parent = nil->left = nil->right = nil;
    }
    Node* search_key(int);
    void insert_node(Node *);
    void delete_node(Node *);
    inline Node *createNode(int k, RB_TREE_COLOR c = RED) {
        Node *newNode = new Node(k, c);
        newNode->parent = newNode->left = newNode->right = nil;
        return newNode;
    }
    // 先序遍历
    void pre_order_traversal() {
        __pre_order_traversal_recure(this->root);
    }
    // 中序遍历
    void in_order_traversal() {
        __in_order_traversal(this->root);
    }
    // 后序遍历
    void post_order_traversal() {
        __post_order_traversal(this->root);
    }
    // 层次遍历，从上到下，从左到右
    void level_order_traversal();
    // 求树高度
    int binary_tree_height() {
        return __binary_tree_height(this->root);
    }
private:
    Node *root;
    Node *nil;
    void rb_insert_fixup(Node *);
    void rb_remove_fixup(Node *);
    void left_rotate(Node *);
    void right_rotate(Node *);
    int __binary_tree_height(Node *);
    void __pre_order_traversal_recure(Node *);
    void __in_order_traversal(Node *);
    void __post_order_traversal(Node *t);
    inline Node *tree_minimum(Node *x) {
        if (x == NULL || x == nil) return NULL;
        while (x->left != nil) x = x->left;
        return x;
    }
};

#endif //EXEC_REDBLACKTREE_H
