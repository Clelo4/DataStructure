//
// Created by jack on 2021/12/4.
//

#ifndef EXEC_RED_BLACK_TREE_H
#define EXEC_RED_BLACK_TREE_H

#include <cstdlib>

// （1）树根为黑色
// （2）外部节点：均为黑色
// （3）其余节点：若为红节点，则只能有黑孩子
// （4）外部节点到根：途中黑节点树木相等

typedef enum RB_TREE_COLOR {
    BLACK,
    RED,
} RB_TREE_COLOR;

class RedBlackTree {
public:
    class Node {
    public:
        int key;
        Node *parent;
        Node *left;
        Node *right;
        RB_TREE_COLOR color;

        explicit Node(int k, RB_TREE_COLOR c = RED) : key(k), parent(nullptr), left(nullptr), right(nullptr),
                                                      color(c) {}
    };

public:
    RedBlackTree() {
        root = nil = new Node(0, BLACK);
        nil->parent = nil->left = nil->right = nil;
    }

    ~RedBlackTree();

    Node *search_key(int);

    /**
     * 插入节点
     * @param z 新节点
     */
    void insert_node(Node *z);

    /**
     * 删除节点
     * @param z 待删除的节点
     */
    void delete_node(Node *z);

    inline Node *createNode(int k, RB_TREE_COLOR c = RED) {
        Node *newNode = new Node(k, c);
        newNode->parent = newNode->left = newNode->right = nil;
        return newNode;
    }

    // 先序遍历
    void pre_order_traversal() { _pre_order_traversal_recursive(this->root); }

    // 中序遍历
    void in_order_traversal() { _in_order_traversal(this->root); }

    // 后序遍历
    void post_order_traversal() { _post_order_traversal(this->root); }

    // 层次遍历，从上到下，从左到右
    void level_order_traversal();

    // 求树高度
    int binary_tree_height() { return _binary_tree_height(this->root); }

private:
    Node *root;
    Node *nil;

    /**
     * 双红修正
     * @param z 要修复的点
     */
    void rb_insert_fixup(Node *z);

    /**
     * 双黑修正
     * @param z 要修复的点
     */
    void rb_remove_fixup(Node *z);

    void left_rotate(Node *);

    void right_rotate(Node *);

    int _binary_tree_height(Node *);

    void _pre_order_traversal_recursive(Node *);

    void _in_order_traversal(Node *);

    void _post_order_traversal(Node *t);

    void _delete_binary_tree(Node *t);

    inline Node *tree_minimum(Node *x) {
        if (x == nullptr || x == nil)
            return nullptr;
        while (x->left != nil)
            x = x->left;
        return x;
    }
};

#endif //EXEC_RED_BLACK_TREE_H
