//
// Created by chengjunjie on 2023/9/20.
//

#ifndef DEMO_BSTARTREE_H
#define DEMO_BSTARTREE_H

#include <vector>

// BStarTree
class BStarTree {
public:
    // BStarTree节点
    class BStarTreeNode {
    public:
        BStarTreeNode();
        ~BStarTreeNode();

        bool is_leaf = false;
        std::vector<int> keys;
        std::vector<BStarTreeNode*> children;
    };

public:
    explicit BStarTree(int degree);
    ~BStarTree();

    /**
     * 查找key，返回包含该key的节点
     * @param key 要查找的key
     * @return 返回包含该key的节点
     */
    BStarTreeNode* search(int key);

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

    static void test();

private:
    // 当前B*树的度
    // 除了根节点，所有节点的孩子数量childNum，满足(4/3)*degree<=childNum<=2*degree
    // 根节点最少可以有2个孩子（当前仅当根节点不是叶子节点），即2<=childNum<=2*degree
    const int degree;

    // min_degree = (4/3)*degree
    const int min_degree;

    // max_degree = 2*degree
    const int max_degree;

    // 树根
    // 如果整棵B树只有一个节点（根节点是叶子节点），则该节点的key数量需要满足0<=Keys<=(2 * degree - 1)
    BStarTreeNode* root;

    /**
     * 在非NULL的target父节点中，查找key，返回包含该key的节点
     * @param key 目标key
     * @param target 子树的根
     * @return 返回包含该key的节点
     */
    BStarTreeNode* search(int key, BStarTreeNode* target);

    /**
     * 在非NULL的target父节点中，插入key
     * @param key 待插入的key
     * @param target 目标节点
     */
    void insert_not_full(int key, BStarTreeNode* target);

    /**
     * 对target节点的孩子i进行分割
     * @param target 目标节点
     * @param i 目标节点的第i个孩子
     */
    void BStarTree_split_root(BStarTreeNode* target, int i) const;

    /**
     * 对target节点的孩子i进行分割
     * @param target 目标节点
     * @param i 目标节点的第i个孩子
     */
    void BStarTree_split_child(BStarTreeNode* target, int i) const;

    /**
     * 在以target为根的树中删除key
     * @param key 待删除的key
     * @param target 树根
     * @return
     */
    bool remove(int key, BStarTreeNode* target);

    /**
     * 将key插入到指定的位置中
     * @param key 要插入的key
     * @param target 目标节点
     * @param index 插入的位置
     */
    static void insert_key(int key, BStarTreeNode* target, int index);

    /**
     * 将child插入到指定的位置中
     * @param child 要插入的孩子
     * @param target 目标节点
     * @param index 插入的位置
     */
    static void insert_child(BStarTreeNode* child, BStarTreeNode* target, int index);

    /**
     * 将指定的位置中的key删除
     * @param target 目标节点
     * @param index 要删除的key的位置
     */
    static void remove_key(BStarTreeNode* target, int index);

    /**
     * 将指定的位置中的child删除
     * @param target 目标节点
     * @param index 要删除的孩子的位置
     */
    static void remove_child(BStarTreeNode* target, int index);

    /**
     * 删除当前以target为根的树的最后一个孩子
     * @param target 当前树的根
     * @return 被删除的孩子
     */
    int remove_last(BStarTreeNode* target);

    /**
     * 删除当前以target为根的树的第一个孩子
     * @param target 当前树的根
     * @return 被删除的孩子
     */
    int remove_first(BStarTreeNode* target);

    /**
     * 在keys查找指定key
     * @param keys keys向量
     * @param key 查找目标
     * @return 返回最小的i，满足key大于keys[i - 1]且key小于等于keys[i]
     */
    static int binary_search(std::vector<int>& keys, int key);

    void merge_three_to_two(BStarTreeNode* parent, int first_idx, int second_idx);
};


#endif //DEMO_BSTARTREE_H
