//
// Created by jack on 17/9/23.
//

#ifndef BINARY_SEARCH_SEARCH_H
#define BINARY_SEARCH_SEARCH_H

class search {
public:
    /**
     * 二分查找算法（基础版本，找不到返回-1）
     * @param len 数组长度
     * @param list 有序数组
     * @param key 待查找的关键字
     * @return 目标关键字的位置，找不到返回-1
     */
    static int binary_search_base_one(int len, int* list, int key);

    /**
     * 二分查找算法（基础版本，找不到返回-1）
     * @param len 数组长度
     * @param list 有序数组
     * @param key 待查找的关键字
     * @return 目标关键字的位置，找不到返回-1
     */
    static int binary_search_base_two(int len, int* list, int key);

    /**
     * 二分查找算法（允许重复元素版本）
     * @param len 数组长度
     * @param list 有序数组
     * @param key 待查找的关键字
     * @return 目标关键字的位置，如果有多个返回最左边的元素、或者返回-1
     */
    static int binary_search_base_duplicate_left_most(int len, int* list, int key);

    /**
     * 二分查找算法（允许重复元素版本）
     * @param len 数组长度
     * @param list 有序数组
     * @param key 待查找的关键字
     * @return 目标关键字的位置，如果有多个返回最右边的元素、或者返回-1
     */
    static int binary_search_base_duplicate_right_most(int len, int* list, int key);

    /**
     * 二分查找算法（非精确+重复元素版本）
     * @param len 数组长度
     * @param list 有序数组
     * @param key 待查找的关键字
     * @return 目标关键字的位置，如果有多个返回最左边的元素、如果不存在对应的key，返回最大的小于key的index，或者-1
     */
    static int binary_search_base_approximate_left_most(int len, int* list, int key);

    /**
     * 二分查找算法（非精确+重复元素版本）
     * @param len 数组长度
     * @param list 有序数组
     * @param key 待查找的关键字
     * @return 目标关键字的位置，如果有多个返回最右边的元素、如果不存在对应的key，返回最小的大于key的index，或者-1
     */
    static int binary_search_base_approximate_right_most(int len, int* list, int key);
};

#endif //BINARY_SEARCH_SEARCH_H
