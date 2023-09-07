//
// Created by jack on 5/9/23.
//

#ifndef SHUFFLE_H
#define SHUFFLE_H

// 洗牌算法
class Shuffle {
public:
    /**
     * The Fisher–Yates shuffle is named after Ronald Fisher and Frank Yates, who first described it
     * 复杂度O(n * n)
     * @param len 数组长度
     * @param origin_list 原始数组
     * @param result_list 结果数组
     */
    static void fisher_yates_origin_shuffle(int len, const int* origin_list, int* result_list);

    /**
     * Richard Durstenfeld 和 Donald Knuth 改进的算法
     * 复杂度O(n)
     * @param len
     * @param origin_list
     */
    static void knuth_shuffle(int len, int* origin_list);
};

#endif //SHUFFLE_H
