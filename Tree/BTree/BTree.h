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

    /**
     * 查找key，返回包含该key的节点
     * @param key 要查找的key
     * @return 返回包含该key的节点
     */
    BTreeNode* search(int key);

    /**
     * 插入key
     * @param key 待插入的key
     */
    void insert(int key);

    /**
     * 删除key
     * @param key 待删除的key
     * @return 是否删除成功
     */
    bool remove(int key);

private:
    // 当前B树的度
    size_t degree;
    // 树根
    BTreeNode* root;

    /**
     * 在非NULL的target父节点中，查找key，返回包含该key的节点
     * @param key 目标key
     * @param target 子树的根
     * @return 返回包含该key的节点
     */
    BTreeNode* search(int key, BTreeNode* target);

    /**
     * 在非NULL的target父节点中，插入key
     * @param key 待插入的key
     * @param target 目标节点
     */
    void insert_not_full(int key, BTreeNode* target);

    /**
     * 对target节点的孩子i进行分割
     * @param target 目标节点
     * @param i 目标节点的第i个孩子
     */
    void BTree_split_child(BTreeNode* target, int i) const;

    /**
     * 在以target为根的树中删除key
     * @param key 待删除的key
     * @param target 树根
     * @return
     */
    bool remove(int key, BTreeNode* target);

    /**
     * 将key插入到指定的位置中
     * @param key 要插入的key
     * @param target 目标节点
     * @param index 插入的位置
     */
    static void insert_key(int key, BTreeNode* target, size_t index);

    /**
     * 将child插入到指定的位置中
     * @param child 要插入的孩子
     * @param target 目标节点
     * @param index 插入的位置
     */
    static void insert_child(BTreeNode* child, BTreeNode* target, size_t index);

    /**
     * 将指定的位置中的key删除
     * @param target 目标节点
     * @param index 要删除的key的位置
     */
    static void remove_key(BTreeNode* target, size_t index);

    /**
     * 将指定的位置中的child删除
     * @param target 目标节点
     * @param index 要删除的孩子的位置
     */
    static void remove_child(BTreeNode* target, size_t index);

    /**
     * 删除当前以target为根的树的最后一个孩子
     * @param target 当前树的根
     * @return 被删除的孩子
     */
    int remove_last(BTreeNode* target);

    /**
     * 删除当前以target为根的树的第一个孩子
     * @param target 当前树的根
     * @return 被删除的孩子
     */
    int remove_first(BTreeNode* target);

    /**
     * 在keys查找指定key
     * @param keys keys向量
     * @param key 查找目标
     * @return 返回最小的i，满足key大于keys[i - 1]且key小于等于keys[i]
     */
    static int binary_search(std::vector<int>& keys, int key);
};

#endif //DEMO_BTREE_H
