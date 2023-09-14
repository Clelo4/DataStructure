//
// Created by jack on 7/9/23.
//

#ifndef RANDOM_SAMPLING_H
#define RANDOM_SAMPLING_H

// 随机采样算法
class RandomSampling {
public:
    /**
     * 加权随机采样（不放回、放回均适用，本此暂时只实现放回版本）
     * @param n 原始权重数组长度
     * @param weighted_list 权重数组
     * @param m 采样数量
     * @param result_list 采样结果数组
     */
    static void weighted_random_sampling_base(int n, const int* weighted_list, int m, int *result_list);

    /**
     * 加权不放回随机采样
     * 算法复杂度：O(mn)
     * @param n 原始权重数组长度
     * @param weighted_list 权重数组
     * @param m 采样数量
     * @param result_list 采样结果数组
     */
    static void weighted_random_sampling(int n, int* weighted_list, int m, int *result_list);

    /**
     * 加权不放回随机采样（BST实现版本）
     * 算法复杂度：O(n + m * log(n))
     * @param n 原始权重数组长度
     * @param weighted_list 权重数组
     * @param m 采样数量
     * @param result_list 采样结果数组
     */
    static void weighted_random_sampling_bst(int n, const int* weighted_list, int m, int *result_list);

    static void weighted_random_sample_alias_method(int n, const int* weighted_list, int m, int* result_list);

    /**
     * 蓄水池抽样算法（适用于未知长度的序列、也适用流处理的情况）
     * 算法复杂度：O(n)
     * @param m 抽样数量
     * @param result_list 抽样结果
     * @param flow_list 任意长度的序列，实际上流序列是任意
     * @param n 序列的长度（实际应该不存在长度，因为序列的长度是任意长度，无法提前知道，这里只是为了方便计算）
     */
    static void reservoir_sampling(int m, int *result_list, const int* flow_list, int n);

    static void weighted_random_sampling_alogorithm_a();

    // https://www.keithschwarz.com/darts-dice-coins/

    // https://lotabout.me/2018/Weighted-Random-Sampling/
};

#endif //RANDOM_SAMPLING_H
