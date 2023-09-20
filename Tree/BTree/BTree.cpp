//
// Created by jack on 16/8/23.
//

#include "BTree.h"

BTree::BTreeNode::BTreeNode() = default;

BTree::BTreeNode::~BTreeNode() {
    for (auto* child : children) {
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
    const size_t len = target->keys.size();
    auto& keys = target->keys;

    int idx = binary_search(keys, key);

    if (idx < len && keys[idx] == key) return target;
    else if (target->is_leaf) return nullptr;
    else return search(key, target->children[idx]);
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
    auto & keys = target->keys;
    int idx = binary_search(keys, key);

    if (target->is_leaf) {
        // 将key插入到该叶子节点
        target->keys.push_back(target->keys.back());
        for (size_t i = target->keys.size() - 1; i > idx; i--) {
            target->keys[i] = target->keys[i - 1];
        }
        target->keys[idx] = key;
    } else {
        BTreeNode* next_target = target->children[idx];
        if (next_target->keys.size() == 2 * degree - 1) {
            // 分割next_target节点
            BTree_split_child(target, idx);
            // 判断key与新的keys[i]节点大小
            if (key > keys[idx]) {
                idx++;
            }
        }
        next_target = target->children[idx];
        insert_not_full(key, next_target);
    }
}

bool BTree::remove(int key) {
    if (root == nullptr) return false;
    return remove(key, root);
}

bool BTree::remove(int key, BTree::BTreeNode *target) {
    auto& keys = target->keys;
    const size_t len = keys.size();

    int idx = binary_search(keys, key);

    bool found = idx < len && keys[idx] == key;

    if (target->is_leaf) {
        if (found) {
            // remove keys[i]
            for (int i = idx; i < len - 1; i++) {
                keys[i] = keys[i + 1];
            }
            keys.resize(len - 1);

            // 重建root
            if (target == root && target->keys.empty()) {
                root = nullptr;
                target->children.resize(0);
                delete target;
            }

            return true;
        }
        return false;
    } else {
        auto & children = target->children;
        if (found) {
            BTreeNode* left_sibling = children[idx];
            BTreeNode* right_sibling = children[idx + 1];
            if (left_sibling->keys.size() >= degree) {
                target->keys[idx] = remove_last(left_sibling);
            } else if (right_sibling->keys.size() >= degree) {
                target->keys[idx] = remove_first(right_sibling);
            } else {
                // 将当前key和right_sibling的所有key移动到left_sibling
                left_sibling->keys.push_back(key);
                for (const auto& move_key : right_sibling->keys) {
                    left_sibling->keys.push_back(move_key);
                }

                // 将right_sibling的所有child移动到left_sibling
                for (const auto& child : right_sibling->children) {
                    left_sibling->children.push_back(child);
                }
                right_sibling->children.resize(0);
                delete right_sibling;

                remove_key(target, idx);
                remove_child(target, idx + 1);

                // 重建root
                if (target == root && target->keys.empty()) {
                    root = left_sibling;
                    target->children.resize(0);
                    delete target;
                }

                return remove(key, left_sibling);
            }

            return true;
        } else {
            auto& next_target = children[idx];
            if (next_target->keys.size() >= degree)
                return remove(key, next_target);

            BTreeNode* left_sibling = (idx > 0) ? children[idx - 1] : nullptr;
            BTreeNode* right_sibling = (idx < len) ? children[idx + 1] : nullptr;

            if (left_sibling != nullptr && left_sibling->keys.size() >= degree) {
                // 将keys[idx - 1]插入到next_target的0位置
                insert_key(keys[idx - 1], next_target, 0);

                // 将left_sibling->keys的最后一个元素移动到keys[idx - 1]
                keys[idx - 1] = left_sibling->keys.back();
                // 删除left_sibling的最后一个key
                remove_key(left_sibling, left_sibling->keys.size() - 1);

                if (!left_sibling->is_leaf) {
                    // 将left_sibling->children.back()插入到next_target的0位置
                    insert_child(left_sibling->children.back(), next_target, 0);

                    // 删除left_sibling的最后一个child
                    remove_child(left_sibling, left_sibling->children.size() - 1);
                }

                return remove(key, next_target);
            } else if (right_sibling != nullptr && right_sibling->keys.size() >= degree) {
                // 将keys[idx]插入到next_target的最后
                insert_key(keys[idx], next_target, next_target->keys.size());

                // 将right_sibling->keys的第一个元素移动到keys[idx]
                keys[idx] = right_sibling->keys.front();
                // 删除right_sibling的第一个key
                remove_key(right_sibling, 0);

                if (!right_sibling->is_leaf) {
                    // 将right_sibling的第一个child插入到next_target的最后
                    insert_child(right_sibling->children.front(), next_target, next_target->children.size());

                    // 删除right_sibling的第一个child
                    remove_child(right_sibling, 0);
                }

                return remove(key, next_target);
            }
            // 合并
            BTreeNode* real_next_target = nullptr;

            if (left_sibling != nullptr) {
                left_sibling->keys.push_back(keys[idx - 1]);
                for (const auto & move_key : next_target->keys) {
                    left_sibling->keys.push_back(move_key);
                }

                for (auto & child : next_target->children) {
                    left_sibling->children.push_back(child);
                }

                // 删除next_target节点
                next_target->children.resize(0);
                delete next_target;

                // 删除keys[idx - 1]
                remove_key(target, idx - 1);
                // 删除children[idx]
                remove_child(target, idx);

                real_next_target = left_sibling;
            } else if (right_sibling != nullptr) {
                next_target->keys.push_back(keys[idx]);
                for (const auto & move_key : right_sibling->keys) {
                    next_target->keys.push_back(move_key);
                }

                for (const auto & child : right_sibling->children) {
                    next_target->children.push_back(child);
                }

                // 删除right_sibling节点
                right_sibling->children.resize(0);
                delete right_sibling;

                // 删除keys[idx]
                remove_key(target, idx);
                // 删除right_sibling
                remove_child(target, idx + 1);

                real_next_target = next_target;
            }

            // 重建root
            if (target == root && target->keys.empty()) {
                root = real_next_target;
                target->children.resize(0);
                delete target;
            }

            return remove(key, real_next_target);
        }
    }
    return false;
}

void BTree::insert_key(int key, BTree::BTreeNode *target, size_t index) {
    target->keys.push_back(key);

    for (size_t i = target->keys.size() - 1; i > index; i--) {
        target->keys[i] = target->keys[i - 1];
    }
    target->keys[index] = key;
}

void BTree::insert_child(BTreeNode* child, BTree::BTreeNode *target, size_t index) {
    target->children.push_back(child);

    for (size_t i = target->keys.size() - 1; i > index; i--) {
        target->children[i] = target->children[i - 1];
    }
    target->children[index] = child;
}

void BTree::remove_key(BTree::BTreeNode *target, size_t index) {
    for(size_t i = index; i < target->keys.size() - 1; i++) {
        target->keys[i] = target->keys[i + 1];
    }
    target->keys.pop_back();
}

void BTree::remove_child(BTree::BTreeNode *target, size_t index) {
    for(size_t i = index; i < target->children.size() - 1; i++) {
        target->children[i] = target->children[i + 1];
    }
    target->children.pop_back();
}

int BTree::remove_last(BTreeNode* target) {
    if (target->is_leaf) {
        const auto res = target->keys.back();
        remove_key(target, target->keys.size() - 1);
        return res;
    } else {
        const size_t idx = target->children.size() - 1;
        const auto& next_target = target->children[idx];
        auto* left_sibling = target->children[idx - 1];

        if (next_target->keys.size() >= degree) return remove_last(next_target);
        else if (left_sibling->keys.size() >= degree) {
            // 将target->keys[idx - 1]插入next_target的头部
            insert_key(target->keys[idx - 1], next_target, 0);
            target->keys[idx - 1] = left_sibling->keys.back();
            // 删除left_sibling的最后一个key
            remove_key(left_sibling, left_sibling->keys.size() - 1);

            if (!left_sibling->is_leaf) {
                // 将left_sibling的最后一个child移动到next_target的头部
                insert_child(left_sibling->children.back(), next_target, 0);
                remove_child(left_sibling, left_sibling->children.size() - 1);
            }

            return remove_last(next_target);
        } else {
            // 移动target->keys[idx - 1]和next_target的所有key到left_sibling
            left_sibling->keys.push_back(target->keys[idx - 1]);
            for (const auto& move_key : next_target->keys) {
                left_sibling->keys.push_back(move_key);
            }

            // 移动next_target的children到left_sibling
            for (const auto& child : next_target->children) {
                left_sibling->children.push_back(child);
            }

            next_target->children.resize(0);
            delete next_target;

            return remove_last(left_sibling);
        }
    }
}

int BTree::remove_first(BTreeNode* target) {
    if (target->is_leaf) {
        const auto res = target->keys.front();
        remove_key(target, 0);
        return res;
    } else {
        const size_t idx = 0;
        const auto& next_target = target->children[idx];
        auto* right_sibling = target->children[idx + 1];

        if (next_target->keys.size() >= degree) return remove_first(next_target);
        else if (right_sibling->keys.size() >= degree) {
            // 将target->keys[idx]插入next_target的尾部
            insert_key(target->keys[idx], next_target, next_target->keys.size());
            target->keys[idx] = right_sibling->keys.front();
            // 删除right_sibling的第一个key
            remove_key(right_sibling, 0);

            if (!right_sibling->is_leaf) {
                // 将right_sibling的第一个child移动到next_target的尾部
                insert_child(right_sibling->children.front(), next_target, next_target->children.size());
                remove_child(right_sibling, 0);
            }

            return remove_first(next_target);
        } else {
            // 移动target->keys[idx]和right_sibling的所有key到next_target
            next_target->keys.push_back(target->keys[idx]);
            for (const auto& move_key : right_sibling->keys) {
                next_target->keys.push_back(move_key);
            }

            // 移动right_sibling的children到next_target
            for (const auto& child : right_sibling->children) {
                next_target->children.push_back(child);
            }

            right_sibling->children.resize(0);
            delete right_sibling;

            return remove_first(next_target);
        }
    }
}

int BTree::binary_search(std::vector<int> &keys, int key) {
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
