//
// Created by jack on 5/9/23.
//

#ifndef SHUFFLE_H
#define SHUFFLE_H

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

    /**
     * 加权不放回随机采样
     * @param len 长度
     * @param weighted_list 权重数组
     * @param result_list 选中的数组元素序列号
     */
    static void weighted_random_sampling(int len, int* weighted_list, int *result_list);

    /**
     * 蓄水池抽样算法（适用于未知长度的序列、也适用流处理的情况）
     * @param k 抽样数量
     * @param result_list 抽样结果
     * @param flow_list 任意长度的序列，实际上流序列是任意
     * @param flow_len 序列的长度（实际应该不存在长度，因为序列的长度是任意长度，无法提前知道，这里只是为了方便计算）
     */
    static void reservoir_sampling(int k, int *result_list, const int* flow_list, int flow_len);
};

#endif //SHUFFLE_H
