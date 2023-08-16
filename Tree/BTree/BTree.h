//
// Created by jack on 16/8/23.
//

#ifndef DEMO_BTREE_H
#define DEMO_BTREE_H


#include <vector>

// BTree
class BTree {
public:
    // BTree节点
    class BTreeNode {
    public:
        BTreeNode();
        ~BTreeNode();

        bool is_leaf = false;
        std::vector<int> keys;
        std::vector<BTreeNode*> children;
    };

public:
    explicit BTree(int degree);
    ~BTree();

    // 查找key，返回包含该key的节点
    BTreeNode* search(int key);
    // 插入key
    void insert(int key);
    // 删除key
    bool remove(int key);

private:
    int degree;
    BTreeNode* root;

    // 在非NULL的target父节点中，查找key，返回包含该key的节点
    BTreeNode* search(int key, BTreeNode* target);

    // 在非NULL的target父节点中，插入key
    void insert_not_full(int key, BTreeNode* target);

    // 对target节点的孩子i进行分割
    void BTree_split_child(BTreeNode* target, int i) const;
};


#endif //DEMO_BTREE_H
