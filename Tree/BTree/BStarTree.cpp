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
    if (degree < 3) exit(-1);
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
    if (root == nullptr) return false;
    return remove(key, root);
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
            // 分割next_target节点
            BStarTree_split_child(target, idx);

            // 重新查询key
            idx = static_cast<int>(binary_search(keys, key));
        }
        next_target = target->children[idx];
        assert(next_target != nullptr);
        insert_not_full(key, next_target);
    }
    if (target != root && !target->is_leaf) {
        assert(target->keys.size() + 1 == target->children.size());
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
        remove_key(current, (int) current->keys.size() - 1);

        if (!right_child->is_leaf) {
            insert_child(current->children.back(), right_child, 0);
            remove_child(current, (int) current->children.size() - 1);
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
        for (int i = new_size + 1; i < left_child->children.size(); i++) {
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

    if (!right_child->is_leaf) {
        for (int i = 0; i < (right_child->children.size() - new_size - 1); i++) {
            new_child->children.push_back(right_child->children[i]);
        }
        right_child->children.erase(right_child->children.begin(), right_child->children.begin() + (int)right_child->children.size() - new_size - 1);
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
        for (int i = half_size + 1; i < child->children.size(); i++) {
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
    auto& keys = target->keys;
    const int len = (int) keys.size();

    int idx = binary_search(keys, key);
    bool found = idx < len && keys[idx] == key;

    if (target->is_leaf) {
        if (found) {
            // remove keys[i]
            remove_key(target, idx);

            if (target == root && target->keys.empty()) {
                root = nullptr;
                target->children.resize(0);
                delete target;
            }
        }
        return false;
    }
    auto& children = target->children;
    if (found) {
        BStarTreeNode* left_sibling = children[idx];
        BStarTreeNode* right_sibling = children[idx + 1];

        if (left_sibling->keys.size() >= min_degree) {
            target->keys[idx] = remove_last(left_sibling);
        } else if (right_sibling->keys.size() >= min_degree) {
            target->keys[idx] = remove_first(right_sibling);
        } else {
            // 合并
            if (target == root && target->keys.size() == 1) {
                BStarTreeNode* left = target->children[0];
                BStarTreeNode* right = target->children[1];
                // 合并left和right
                left->keys.push_back(target->keys[0]);
                for (auto x : right->keys) left->keys.push_back(x);
                for (auto child : right->children) left->children.push_back(child);
                right->children.resize(0);
                delete right;
                target->children.resize(0);
                delete target;

                root = left;
                return remove(key, root);
            }

            // 合并3个节点成2个
            if (idx == 0) {
                merge_three_to_two(target, idx, idx + 1);
            } else if (idx >= keys.size()) {
                merge_three_to_two(target, idx - 2, idx - 1);
            } else {
                merge_three_to_two(target, idx - 1, idx);
            }
            return remove(key, target);
        }

        return true;
    } else {
        auto next_target = children[idx];
        if (next_target->keys.size() >= min_degree) {
            return remove(key, next_target);
        }

        BStarTreeNode* left_sibling = (idx >= 1) ? children[idx - 1] : nullptr;
        BStarTreeNode* right_sibling = (idx + 1 < children.size()) ? children[idx + 1] : nullptr;

        if (left_sibling != nullptr && left_sibling->keys.size() >= min_degree) {
            // 将父节点的key插入到next_target的头部
            insert_key(keys[idx - 1], next_target, 0);

            // 将左兄弟的最后一个key移动到父节点
            keys[idx - 1] = left_sibling->keys.back();
            remove_key(left_sibling, static_cast<int>(left_sibling->keys.size()) - 1);

            if (!left_sibling->is_leaf) {
                insert_child(left_sibling->children.back(), next_target, 0);
                remove_child(left_sibling, static_cast<int>(left_sibling->children.size()) - 1);
            }

            return remove(key, next_target);
        }
        if (right_sibling != nullptr && right_sibling->keys.size() >= min_degree) {
            // 将父节点的插入next_target的尾部
            insert_key(keys[idx], next_target, static_cast<int>(next_target->keys.size()));

            keys[idx] = right_sibling->keys.front();
            remove_key(right_sibling, 0);

            if (!right_sibling->is_leaf) {
                insert_child(right_sibling->children.front(), next_target, static_cast<int>(next_target->children.size()));

                remove_child(right_sibling, 0);
            }

            return remove(key, next_target);
        }
        // 合并
        if (target == root && target->keys.size() == 1) {
            BStarTreeNode* left = target->children[0];
            BStarTreeNode* right = target->children[1];
            // 合并left和right
            left->keys.push_back(target->keys[0]);
            for (auto x : right->keys) left->keys.push_back(x);
            for (auto child : right->children) left->children.push_back(child);
            right->children.resize(0);
            delete right;
            target->children.resize(0);
            delete target;

            root = left;
            return remove(key, root);
        }

        // 合并3个节点成2个
        if (idx == 0) {
            merge_three_to_two(target, idx, idx + 1);
        } else if (idx >= keys.size()) {
            merge_three_to_two(target, idx - 2, idx - 1);
        } else {
            merge_three_to_two(target, idx - 1, idx);
        }
        return remove(key, target);
    }

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
    if (target->is_leaf) {
        const auto res = target->keys.back();
        remove_key(target, static_cast<int>(target->keys.size()) - 1);
        return res;
    } else {
        const int idx = static_cast<int>(target->children.size()) - 1;
        const auto next_target = target->children[idx];
        auto* left_sibling = target->children[idx - 1];

        if (next_target->keys.size() >= min_degree) return remove_last(next_target);
        else if (left_sibling->keys.size() >= min_degree) {
            // 将target->keys[idx - 1]插入next_target的头部
            insert_key(target->keys[idx - 1], next_target, 0);
            // 将left_sibling的尾部插入target->keys[idx - 1]位置
            target->keys[idx - 1] = left_sibling->keys.back();
            // 删除left_sibling的最后一个key
            remove_key(left_sibling, static_cast<int>(left_sibling->keys.size()) - 1);

            if (!left_sibling->is_leaf) {
                // 将left_sibling的最后一个child移动到next_target的头部
                insert_child(left_sibling->children.back(), next_target, 0);
                remove_child(left_sibling, static_cast<int>(left_sibling->children.size()) - 1);
            }

            return remove_last(next_target);
        } else {
            merge_three_to_two(target, (int)target->keys.size() - 2, (int)target->keys.size() - 1);
            return remove_last(target);
        }
    }
}

int BStarTree::remove_first(BStarTree::BStarTreeNode *target) {
    if (target->is_leaf) {
        const auto res = target->keys.front();
        remove_key(target, 0);
        return res;
    } else {
        const int idx = 0;
        const auto next_target = target->children[idx];
        auto *right_sibling = target->children[idx + 1];

        if (next_target->keys.size() >= min_degree) return remove_first(next_target);
        else if (right_sibling->keys.size() >= min_degree) {
            // 将target->keys[idx]插入next_target的尾部
            insert_key(target->keys[idx], next_target, static_cast<int>(next_target->keys.size()));
            // right_sibling的头部插入target->keys[idx]的位置
            target->keys[idx] = right_sibling->keys.front();
            // 删除right_sibling的第一个key
            remove_key(right_sibling, 0);

            if (!right_sibling->is_leaf) {
                // 将right_sibling的第一个child移动到next_target的尾部
                insert_child(right_sibling->children.front(), next_target, static_cast<int>(next_target->children.size()));
                remove_child(right_sibling, 0);
            }

            return remove_first(next_target);
        }
        else {
            merge_three_to_two(target, 0, 1);
            return remove_last(target);
        }
    }
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

void BStarTree::merge_three_to_two(BStarTree::BStarTreeNode *parent, int first_idx, int second_idx) {
    const int half_key_size = 3 * min_degree / 2 - 1;

    auto total_keys = parent->children[first_idx]->keys;
    total_keys.push_back(parent->keys[first_idx]);
    for (auto key : parent->children[second_idx]->keys) {
        total_keys.push_back(key);
    }
    total_keys.push_back(parent->keys[second_idx]);
    for (auto key : parent->children[second_idx + 1]->keys) {
        total_keys.push_back(key);
    }

    auto total_children = parent->children[first_idx]->children;
    for (auto child : parent->children[second_idx]->children) {
        total_children.push_back(child);
    }
    for (auto child : parent->children[second_idx + 1]->children) {
        total_children.push_back(child);
    }

    auto* new_left = new BStarTreeNode();
    auto* new_right = new BStarTreeNode();
    new_left->is_leaf = parent->children[first_idx]->is_leaf;
    new_right->is_leaf = parent->children[first_idx]->is_leaf;

    for (int i = 0; i < half_key_size; i++) {
        new_left->keys.push_back(total_keys[i]);
    }
    int new_middle_key = total_keys[half_key_size];
    for (int i = half_key_size + 1; i < total_keys.size(); i++) {
        new_right->keys.push_back(total_keys[i]);
    }
    if (!new_left->is_leaf) {
        for (int i = 0; i < half_key_size + 1; i++) {
            new_left->children.push_back(total_children[i]);
        }
        for (int i = half_key_size + 1; i < total_children.size(); i++) {
            new_right->children.push_back(total_children[i]);
        }
    }
    parent->children[first_idx]->children.resize(0);
    parent->children[first_idx + 1]->children.resize(0);
    parent->children[first_idx + 2]->children.resize(0);
    delete parent->children[first_idx];
    delete parent->children[first_idx + 1];
    delete parent->children[first_idx + 2];

    parent->keys[first_idx] = new_middle_key;
    parent->children[first_idx] = new_left;
    parent->children[second_idx] = new_right;

    remove_key(parent, second_idx);
    remove_child(parent, second_idx + 1);
}

void BStarTree::test() {
    BStarTree bStarTree(7);
    for (int i = 1; i < 10000; i++) {
        bStarTree.insert(i);
    }

    for (int i = 1000; i > 1; i--) {
        assert(bStarTree.search(i) != nullptr);
    }

    bStarTree.search(30);
    for (int i = 4000; i > 1000; i--) {
        bStarTree.remove(i);
    }
    for (int i = 9000; i > 1000; i--) {
        bStarTree.remove(i);
    }
    for (int i = 4000; i > 1000; i--) {
        assert(bStarTree.search(i) == nullptr);
    }
    for (int i = 10000; i > 900; i--) {
        if (i % 3) {
            bStarTree.insert(i);
        }
    }
    for (int i = 10000; i > 900; i--) {
        if (i % 3) {
            assert(bStarTree.search(i) != nullptr);
        }
    }
    for (int i = 500; i < 700; i++) {
        bStarTree.remove(i);
    }
    for (int i = 500; i < 700; i++) {
        assert(bStarTree.search(i) == nullptr);
    }
}
