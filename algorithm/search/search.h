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
    int binary_search_base_one(int len, int* list, int key);

    /**
     * 二分查找算法（基础版本，找不到返回-1）
     * @param len 数组长度
     * @param list 有序数组
     * @param key 待查找的关键字
     * @return 目标关键字的位置，找不到返回-1
     */
    int binary_search_base_tow(int len, int* list, int key);
};

#endif //BINARY_SEARCH_SEARCH_H
