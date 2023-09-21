//
// Created by chengjunjie on 2023/9/20.
//

#ifndef DEMO_BPLUSTREE_H
#define DEMO_BPLUSTREE_H

#include <vector>

class BTreeNode {
public:
    BTreeNode();
    ~BTreeNode();
    bool is_leaf = false;
    std::vector<int> keys;
    std::vector<int> values;
    // 重要：left_child <= parent < right_child
    std::vector<BTreeNode*> children;
    BTreeNode* next = nullptr;
};

// B+树与B树的区别：
// 1. 非叶子节点只存储key，不存储值
// 2. 叶子节点同时存储key和值
// 3. 每个叶子节点含有指向下一个相邻叶子节点的指针
class BPlusTree {
public:
    explicit BPlusTree(int degree);
    ~BPlusTree();

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
    void insert(int key, int value);

    /**
     * 删除key
     * @param key 待删除的key
     * @return 是否删除成功
     */
    bool remove(int key);

    static void test();

private:
    // 当前B+树的度
    // 除了根节点，所有节点的孩子数量childNum，满足degree<=childNum<=2*degree
    // 根节点最少可以有2个孩子（当前仅当根节点不是叶子节点），即2<=childNum<=2*degree
    int degree;

    // 树根
    // 如果整棵B+树只有一个节点（根节点是叶子节点），则该节点的key数量需要满足0<=Keys<=(2 * degree - 1)
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
    void insert_not_full(int key, int value, BTreeNode* target);

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
    static void insert_key(int key, BTreeNode* target, int index);

    static void insert_value(int value, BTreeNode* target, int index);

    /**
     * 将child插入到指定的位置中
     * @param child 要插入的孩子
     * @param target 目标节点
     * @param index 插入的位置
     */
    static void insert_child(BTreeNode* child, BTreeNode* target, int index);

    /**
     * 将指定的位置中的key删除
     * @param target 目标节点
     * @param index 要删除的key的位置
     */
    static void remove_key(BTreeNode* target, int index);

    /**
     * 将指定的位置中的child删除
     * @param target 目标节点
     * @param index 要删除的孩子的位置
     */
    static void remove_child(BTreeNode* target, int index);

    static void remove_value(BTreeNode* target, int index);

    /**
     * 在keys查找指定key
     * @param keys keys向量
     * @param key 查找目标
     * @return 返回最小的i，满足key大于keys[i - 1]且key小于等于keys[i]
     */
    static int binary_search(std::vector<int>& keys, int key);

    static int get_last_key(BTreeNode* target);
};


#endif //DEMO_BPLUSTREE_H
