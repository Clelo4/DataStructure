//
// Created by chengjunjie on 2023/9/20.
//

#include "BPlusTree.h"
#include <iostream>

BTreeNode::BTreeNode() = default;

BTreeNode::~BTreeNode() = default;

BPlusTree::BPlusTree(int degree): degree(degree), root(nullptr) {
}

BPlusTree::~BPlusTree() {
    delete root;
}

BTreeNode *BPlusTree::search(int key) {
    if (root == nullptr) return nullptr;
    return search(key, root);
}

BTreeNode *BPlusTree::search(int key, BTreeNode *target) {
    const int len = static_cast<int>(target->keys.size());
    auto& keys = target->keys;

    int idx = binary_search(keys, key);

    if (target->is_leaf) {
        if (idx < len && keys[idx] == key) return target;
        else return nullptr;
    } else {
        return search(key, target->children[idx]);
    }
}

int BPlusTree::binary_search(std::vector<int> &keys, int key) {
    const int n = static_cast<int>(keys.size());
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

void BPlusTree::insert(int key, int value) {
    if (root == nullptr) {
        root = new BTreeNode();
        root->keys.push_back(key);
        root->values.push_back(value);
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
    insert_not_full(key, value, root);
}

void BPlusTree::BTree_split_child(BTreeNode *target, int index) const {
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
        if (child->is_leaf) {
            new_child->values.push_back(child->values[i]);
        }
    }

    // 清空尾部节点
    if (!child->is_leaf) {
        child->keys.resize(degree - 1);
    } else {
        // 由于叶子节点的key不能提升到中间节点，所以左边的叶子节点的key会多出一个，这个key等于新的中间节点key
        child->keys.resize(degree);
        child->values.resize(degree);
    }

    // 将middle_key填入target->keys的index位置
    insert_key(middle_key, target, index);

    // 将new_child填入target->children的index+1位置
    insert_child(new_child, target, index+1);

    if (child->is_leaf) {
        // 连接两个叶子节点
        new_child->next = child->next;
        child->next = new_child;
    }
}

void BPlusTree::insert_not_full(int key, int value, BTreeNode* target) {
    auto & keys = target->keys;
    int idx = binary_search(keys, key);

    if (target->is_leaf) {
        // 将key插入到该叶子节点
        insert_key(key, target, idx);
        insert_value(value, target, idx);
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
        insert_not_full(key, value, next_target);
    }
}

bool BPlusTree::remove(int key) {
    if (root == nullptr) return false;
    return remove(key, root);
}

bool BPlusTree::remove(int key, BTreeNode* target) {
    auto& keys = target->keys;
    const size_t len = keys.size();

    int idx = binary_search(keys, key);

    bool found = idx < len && keys[idx] == key;

    if (target->is_leaf) {
        if (found) {
            // remove keys[i]
            remove_key(target, idx);
            // remove values[i]
            remove_value(target, idx);

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
        auto& children = target->children;
        auto next_target = children[idx];
        if (next_target->keys.size() >= degree)
            return remove(key, next_target);

        BTreeNode* left_sibling = (idx >= 1) ? children[idx - 1] : nullptr;
        BTreeNode* right_sibling = (idx + 1 < children.size()) ? children[idx + 1] : nullptr;

        if (left_sibling != nullptr && left_sibling->keys.size() >= degree) {
            if (!left_sibling->is_leaf) {
                // 将keys[idx - 1]插入到next_target的0位置
                insert_key(keys[idx - 1], next_target, 0);

                // 将left_sibling->keys的最后一个元素移动到keys[idx - 1]
                keys[idx - 1] = left_sibling->keys.back();
                // 删除left_sibling的最后一个key
                remove_key(left_sibling,  static_cast<int>(left_sibling->keys.size()) - 1);

                // 将left_sibling->children.back()插入到next_target的0位置
                insert_child(left_sibling->children.back(), next_target, 0);

                // 删除left_sibling的最后一个child
                remove_child(left_sibling, static_cast<int>(left_sibling->children.size()) - 1);
            } else {
                // 将left_sibling.back()插入到next_target的0位置
                insert_key(left_sibling->keys.back(), next_target, 0);

                // 删除left_sibling的最后一个key
                remove_key(left_sibling,  static_cast<int>(left_sibling->keys.size()) - 1);

                keys[idx - 1] = left_sibling->keys.back();

                // 将left_sibling->values.back()插入到next_target的0位置
                insert_value(left_sibling->values.back(), next_target, 0);

                // 删除left_sibling的最后一个values
                remove_value(left_sibling, static_cast<int>(left_sibling->values.size()) - 1);
            }


            return remove(key, next_target);
        } else if (right_sibling != nullptr && right_sibling->keys.size() >= degree) {
            if (!right_sibling->is_leaf) {
                // 将keys[idx]插入到next_target的最后
                insert_key(keys[idx], next_target, static_cast<int>(next_target->keys.size()));

                // 将right_sibling->keys的第一个元素移动到keys[idx]
                keys[idx] = right_sibling->keys.front();
                // 删除right_sibling的第一个key
                remove_key(right_sibling, 0);

                // 将right_sibling的第一个child插入到next_target的最后
                insert_child(right_sibling->children.front(), next_target, static_cast<int>(next_target->children.size()));

                // 删除right_sibling的第一个child
                remove_child(right_sibling, 0);
            } else {
                // 将right_sibling->keys.front()插入到next_target的最后
                insert_key(right_sibling->keys.front(), next_target, static_cast<int>(next_target->keys.size()));

                // 将next_target->keys的最后一个元素移动到keys[idx]
                keys[idx] = next_target->keys.back();

                // 删除right_sibling的第一个key
                remove_key(right_sibling, 0);

                // 将right_sibling的第一个value插入到next_target的最后
                insert_value(right_sibling->values.front(), next_target, static_cast<int>(next_target->values.size()));

                // 删除right_sibling的第一个value
                remove_value(right_sibling, 0);
            }

            return remove(key, next_target);
        }
        // 合并
        BTreeNode* real_next_target = nullptr;

        if (left_sibling != nullptr) {
            if (!next_target->is_leaf)
                left_sibling->keys.push_back(keys[idx - 1]);
            for (const auto move_key : next_target->keys) {
                left_sibling->keys.push_back(move_key);
            }

            if (!next_target->is_leaf) {
                for (auto child : next_target->children) {
                    left_sibling->children.push_back(child);
                }
            } else {
                for (auto value : next_target->values) {
                    left_sibling->values.push_back(value);
                }
            }

            // 删除keys[idx - 1]
            remove_key(target, idx - 1);
            // 删除children[idx]
            remove_child(target, idx);

            real_next_target = left_sibling;

            if (next_target->is_leaf) {
                left_sibling->next = next_target->next;
            }

            // 删除next_target节点
            next_target->children.resize(0);
            delete next_target;
        } else if (right_sibling != nullptr) {
            if (!next_target->is_leaf)
                next_target->keys.push_back(keys[idx]);
            for (const auto move_key : right_sibling->keys) {
                next_target->keys.push_back(move_key);
            }

            if (!next_target->is_leaf) {
                for (const auto child: right_sibling->children) {
                    next_target->children.push_back(child);
                }
            } else {
                for (const auto value: right_sibling->values) {
                    next_target->values.push_back(value);
                }
            }

            // 删除keys[idx]
            remove_key(target, idx);
            // 删除right_sibling
            remove_child(target, idx + 1);

            real_next_target = next_target;

            if (next_target->is_leaf) {
                next_target->next = right_sibling->next;
            }

            // 删除right_sibling节点
            right_sibling->children.resize(0);
            delete right_sibling;
        }

        // 重建root
        if (target == root && target->keys.empty()) {
            root = real_next_target;
            target->children.resize(0);
            delete target;
        }

        return remove(key, real_next_target);
    }
    return false;
}

void BPlusTree::insert_key(int key, BTreeNode *target, int index) {
    target->keys.insert(target->keys.begin() + index, key);
}

void BPlusTree::insert_value(int value, BTreeNode *target, int index) {
    target->values.insert(target->values.begin() + index, value);
}

void BPlusTree::insert_child(BTreeNode* child, BTreeNode *target, int index) {
    target->children.insert(target->children.begin() + index, child);
}

void BPlusTree::remove_key(BTreeNode *target, int index) {
    target->keys.erase(target->keys.begin() + index);
}

void BPlusTree::remove_child(BTreeNode *target, int index) {
    target->children.erase(target->children.begin() + index);
}

void BPlusTree::remove_value(BTreeNode *target, int index) {
    target->values.erase(target->values.begin() + index);
}

void BPlusTree::test() {
    BPlusTree btree(6);
    for (int i = 1; i < 19999; i++) {
        btree.insert(i, i);
    }

    for (int i = 100; i < 19999; i++) {
        assert(btree.search(i) != nullptr);
    }

    btree.remove(52);
    assert(btree.search(52) == nullptr);
    assert(btree.search(1) != nullptr);

    auto finded = btree.search(30);
    if (finded != nullptr) {
        for (auto key : finded->keys) {
            std::cout << key << " ";
        }
        std::cout << std::endl;
    }

    btree.search(30);
    for (int i = 2000; i > 100; i--) {
        btree.remove(i);
    }
    for (int i = 2000; i > 100; i--) {
        assert(btree.search(i) == nullptr);
    }
    for (int i = 200; i > 0; i--) {
        if (i % 3) {
            btree.insert(i, i);
        }
    }
    for (int i = 200; i > 0; i--) {
        if (i % 3) {
            assert(btree.search(i) != nullptr);
        }
    }
    for (int i = 500; i < 700; i++) {
        btree.remove(i);
    }
    for (int i = 500; i < 700; i++) {
        assert(btree.search(i) == nullptr);
    }

    auto head = btree.search(1);

    btree.remove(19997);

    while (head) {
        std::cout << head << std::endl;
        for (auto& i : head->values) {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        head = head->next;
    }
}
