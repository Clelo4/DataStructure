//
// Created by chengjunjie on 2023/9/20.
//

#include "BStarTree.h"

BStarTree::BStarTreeNode::BStarTreeNode() = default;

BStarTree::BStarTreeNode::~BStarTreeNode() {
    for (auto* child : children) {
        delete child;
    }
}

BStarTree::BStarTree(int degree): degree(degree), root(nullptr), min_degree(degree * 4 / 3), max_degree(degree * 2) {
}

BStarTree::~BStarTree() {
    delete root;
}

BStarTree::BStarTreeNode *BStarTree::search(int key) {
    if (root == nullptr) return nullptr;
    return search(key, root);
}

void BStarTree::insert(int key) {
    if (root == nullptr) {
        root = new BStarTreeNode();
        root->is_leaf = true;
        root->keys.push_back(key);
        return;
    }

    // 根节点特殊处理
    if (root->keys.size() == (2 * min_degree) - 1) {
        // 创建新的root节点
        auto* new_root = new BStarTreeNode();
        new_root->children.push_back(root);
        root = new_root;

        // 分割new_root
        BStarTree_split_root(new_root, 0);
    }

    insert_not_full(key, root);
}

bool BStarTree::remove(int key) {
    return false;
}

BStarTree::BStarTreeNode *BStarTree::search(int key, BStarTree::BStarTreeNode *target) {
    const int len = static_cast<int>(target->keys.size());
    auto& keys = target->keys;

    int idx = binary_search(keys, key);

    if (idx < len && keys[idx] == key) return target;
    if (target->is_leaf) return nullptr;
    return search(key, target->children[idx]);
}

void BStarTree::insert_not_full(int key, BStarTree::BStarTreeNode *target) {
    auto& keys = target->keys;
    int idx = static_cast<int>(binary_search(keys, key));

    if (target->is_leaf) {
        // 将key插入到该叶子节点
        insert_key(key, target, idx);
    } else {
        BStarTreeNode* next_target = target->children[idx];
        if (next_target->keys.size() == max_degree - 1) {
            if (key == 264) {
                int a = 12;
            }
            // 分割next_target节点
            BStarTree_split_child(target, idx);

            // 重新查询key
            idx = static_cast<int>(binary_search(keys, key));
        }
        next_target = target->children[idx];
        assert(next_target != nullptr);
        insert_not_full(key, next_target);
    }
}

void BStarTree::BStarTree_split_child(BStarTree::BStarTreeNode *target, int index) const {
    auto current = target->children[index];

    // 检查左兄弟是否有空间
    if (index > 0 && target->children[index - 1]->keys.size() < max_degree - 1) {
        auto left_child = target->children[index - 1];
        // 将target->keys[index - 1]插入left_child的最后
        insert_key(target->keys[index - 1], left_child, (int) left_child->keys.size());
        target->keys[index - 1] = current->keys.front();
        // 移除current的第一个key
        remove_key(current, 0);

        if (!left_child->is_leaf) {
            insert_child(current->children.front(), left_child, (int) left_child->children.size());
            remove_child(current, 0);
        }
        return;
    }
    // 检查右兄弟是否有空间
    if (index + 1 < target->children.size() && target->children[index + 1]->keys.size() < max_degree - 1) {
        auto right_child = target->children[index + 1];
        // 将target->keys[index]插入right_child的第一个
        insert_key(target->keys[index], right_child, 0);
        target->keys[index] = current->keys.back();
        // 移除current的最后一个key
        remove_key(current, (int) current->keys.size());

        if (!right_child->is_leaf) {
            insert_child(current->children.back(), right_child, 0);
            remove_child(current, (int) current->children.size());
        }
        return;
    }

    // 拆分child
    int left, right;

    int new_size = min_degree - 1;
    if (index > 0) {
        left = index - 1;
        right = index;
    } else {
        left = index;
        right = index + 1;
    }
    auto left_child = target->children[left];
    auto right_child = target->children[right];

    auto new_child = new BStarTreeNode();
    new_child->is_leaf = left_child->is_leaf;

    // 将左边的后几个移动到new_child
    for (int i = new_size + 1; i < left_child->keys.size(); i++) {
        new_child->keys.push_back(left_child->keys[i]);
    }
    // 在尾部填充target->keys[left]
    new_child->keys.push_back(target->keys[left]);
    // 在target->keys[left]添加left_child->keys[new_size]
    target->keys[left] = left_child->keys[new_size];

    if (!left_child->is_leaf) {
        for (int i = new_size; i < left_child->children.size(); i++) {
            new_child->children.push_back(left_child->children[i]);
        }
        left_child->children.resize(new_size + 1);
    }
    left_child->keys.resize(new_size);

    // 将右边的前right_child->keys.size() - new_size - 1个key移动到new_child
    for (int i = 0; i < (right_child->keys.size() - new_size - 1); i++) {
        new_child->keys.push_back(right_child->keys[i]);
    }
    int middle_key = right_child->keys[right_child->keys.size() - new_size - 1];
    right_child->keys.erase(right_child->keys.begin(), right_child->keys.begin() + (int)right_child->keys.size() - new_size);

    if (!left_child->is_leaf) {
        for (int i = 0; i < (right_child->keys.size() - new_size); i++) {
            new_child->children.push_back(right_child->children[i]);
        }
        right_child->children.erase(right_child->children.begin(), right_child->children.begin() + (int)right_child->keys.size() - new_size);
    }

    // 将middle_key填入target->keys的left+1位置
    insert_key(middle_key, target, left + 1);

    // 将new_child填入target->children的left+1位置
    insert_child(new_child, target, left + 1);
}

void BStarTree::BStarTree_split_root(BStarTree::BStarTreeNode *target, int index) const {
    // 拆分child
    auto child = target->children[index];
    auto new_child = new BStarTreeNode();
    new_child->is_leaf = child->is_leaf;

    int half_size = child->keys.size() / 2;
    int middle_key = child->keys[half_size];

    if (!child->is_leaf) {
        for (int i = half_size + 1; i <= child->keys.size(); i++) {
            new_child->children.push_back(child->children[i]);
        }
        child->children.resize(half_size + 1);
    }

    for (int i = half_size + 1; i < child->keys.size(); i++) {
        new_child->keys.push_back(child->keys[i]);
    }
    // 清空尾部节点
    child->keys.resize(half_size);

    // 将middle_key填入target->keys的index位置
    insert_key(middle_key, target, index);

    // 将new_child填入target->children的index+1位置
    insert_child(new_child, target, index + 1);
}

bool BStarTree::remove(int key, BStarTree::BStarTreeNode *target) {
    return false;
}

void BStarTree::insert_key(int key, BStarTree::BStarTreeNode *target, int index) {
    target->keys.insert(target->keys.begin() + index, key);
}

void BStarTree::insert_child(BStarTree::BStarTreeNode *child, BStarTree::BStarTreeNode *target, int index) {
    target->children.insert(target->children.begin() + index, child);
}

void BStarTree::remove_key(BStarTree::BStarTreeNode *target, int index) {
    target->keys.erase(target->keys.begin() + index);
}

void BStarTree::remove_child(BStarTree::BStarTreeNode *target, int index) {
    target->children.erase(target->children.begin() + index);
}

int BStarTree::remove_last(BStarTree::BStarTreeNode *target) {
    return 0;
}

int BStarTree::remove_first(BStarTree::BStarTreeNode *target) {
    return 0;
}

int BStarTree::binary_search(std::vector<int> &keys, int key) {
    const int n = (int) keys.size();
    int left = 0, right = n;

    while (left < right) {
        int middle = (left + right) / 2;
        if (keys[middle] < key) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}

void BStarTree::test() {
    BStarTree bStarTree(7);
    for (int i = 1; i < 2000; i++) {
        bStarTree.insert(i);
    }

//    for (int i = 1000; i > 1; i--) {
//        assert(bStarTree.search(i) != nullptr);
//    }
}
