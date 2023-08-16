//
// Created by jack on 16/8/23.
//

#include "BTree.h"

BTree::BTreeNode::BTreeNode() = default;

BTree::BTreeNode::~BTreeNode() {
    for (BTreeNode* child : children) {
        delete child;
    }
}

BTree::BTree(int degree): degree(degree), root(nullptr) {}

BTree::~BTree() {
    delete root;
}

BTree::BTreeNode* BTree::search(int key) {
    if (root == nullptr) return nullptr;
    return search(key, root);
}

BTree::BTreeNode* BTree::search(int key, BTreeNode* target) {
    const size_t n = target->keys.size();
    int i = 0;
    auto& keys = target->keys;

    while (i < n && keys[i] < key) {
        i++;
    }

    if (i < n && keys[i] == key) return target;
    else if (target->is_leaf) return nullptr;
    else return search(key, target->children[i]);
}

void BTree::insert(int key) {
    if (root == nullptr) {
        root = new BTreeNode();
        root->keys.push_back(key);
        root->is_leaf = true;
        return;
    }

    // 检查root节点数是否等于（2 * degree - 1）
    if (root->keys.size() == 2 * degree - 1) {
        // 创建新root节点
        auto* new_root = new BTreeNode();
        new_root->children.push_back(root);
        root = new_root;

        // 分割new_root
        BTree_split_child(new_root, 0);
    }
    insert_not_full(key, root);
}

void BTree::BTree_split_child(BTreeNode* target, int index) const {
    // 拆分child
    BTreeNode* child = target->children[index];
    auto* new_child = new BTreeNode();
    new_child->is_leaf = child->is_leaf;

    // child共用（2 * degree - 1）个节点
    int middle_key = child->keys[degree - 1];

    if (!child->is_leaf) {
        for (int i = degree; i < (2 * degree); i++) {
            new_child->children.push_back(child->children[i]);
        }
        // 清空尾部孩子
        child->children.resize(degree);
    }

    for (int i = degree; i < (2 * degree - 1); i++) {
        new_child->keys.push_back(child->keys[i]);
    }
    // 清空尾部节点
    child->keys.resize(degree - 1);

    // 将middle_key填入target->keys的index位置
    if (!target->keys.empty()) {
        target->keys.push_back(target->keys.back());
        for (size_t i = target->keys.size() - 1; i > index; i--) {
            target->keys[i] = target->keys[i - 1];
        }
        target->keys[index] = middle_key;
    }
    else target->keys.push_back(middle_key);

    // 将new_child填入target->children的index位置
    target->children.push_back(target->children.back());
    for (size_t i = target->children.size() - 1; i > index + 1; i--) {
        target->children[i] = target->children[i - 1];
    }
    target->children[index + 1] = new_child;
}

void BTree::insert_not_full(int key, BTreeNode* target) {
    const size_t n = target->keys.size();
    int i = 0;
    auto & keys = target->keys;
    while (i < n && keys[i] < key) {
        i++;
    }

    if (target->is_leaf) {
        // 将key插入到该叶子节点
        target->keys.push_back(target->keys.back());
        for (size_t idx = target->keys.size() - 1; idx > i; idx--) {
            target->keys[idx] = target->keys[idx - 1];
        }
        target->keys[i] = key;
    } else {
        BTreeNode* next_target = target->children[i];
        if (next_target->keys.size() == 2 * degree - 1) {
            // 分割next_target节点
            BTree_split_child(target, i);
            // 判断key与新的keys[i]节点大小
            if (key > keys[i]) {
                i++;
            }
        }
        next_target = target->children[i];
        insert_not_full(key, next_target);
    }
}

bool BTree::remove(int key) {
    return false;
}
