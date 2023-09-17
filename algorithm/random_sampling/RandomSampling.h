//
// Created by jack on 7/9/23.
//

#ifndef RANDOM_SAMPLING_H
#define RANDOM_SAMPLING_H

// 随机采样算法
class RandomSampling {
private:
    static time_t seed;
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
     * 加权放回随机采样（BST实现版本）
     * 算法复杂度：O(n + m * log(n))
     * @param n 原始权重数组长度
     * @param weighted_list 权重数组
     * @param m 采样数量
     * @param result_list 采样结果数组
     */
    static void weighted_random_sampling_bst(int n, const int* weighted_list, int m, int *result_list);

    /**
     * 加权不放回随机采样（BST实现版本）
     * 算法复杂度：O(n + m * log(n))
     * @param n 原始权重数组长度
     * @param weighted_list 权重数组
     * @param m 采样数量
     * @param result_list 采样结果数组
     */
    static void weighted_random_sampling_bst_no_put_back(int n, const int* weighted_list, int m, int *result_list);

    /**
     * 加权放回随机采样（二分查找实现版本）
     * 算法复杂度：O(n + m * log(n))
     * @param n 原始权重数组长度
     * @param weighted_list 权重数组
     * @param m 采样数量
     * @param result_list 采样结果数组
     */
    static void weighted_random_sampling_binary_search(int n, const int* weighted_list, int m, int *result_list);

    /**
     * Alias method 加权放回随机采样（朴素实现版本）
     * 算法复杂度：初始化O(n * n)、单次取样Θ(1)
     * https://www.keithschwarz.com/darts-dice-coins/
     * @param n 原始权重数组长度
     * @param weighted_list 权重数组
     * @param m 采样数量
     * @param result_list 采样结果数组
     */
    static void weighted_random_sample_alias_method_navie(int n, const double* weighted_list, int m, int* result_list);

    /**
     * Alias method 加权放回随机采样（bst实现版本）
     * 算法复杂度：初始化O(n * log(n))、单次取样Θ(1)
     * https://www.keithschwarz.com/darts-dice-coins/
     * @param n 原始权重数组长度
     * @param weighted_list 权重数组
     * @param m 采样数量
     * @param result_list 采样结果数组
     */
    static void weighted_random_sample_alias_method_bst(int n, const double* weighted_list, int m, int* result_list);

    /**
     * Alias method 加权放回随机采样（Vose 实现版本）
     * 算法复杂度：初始化O(n)、单次取样Θ(1)
     * 该alias method实现版本是最佳实践，可能解决由于浮点运算精度导致的问题
     * https://www.keithschwarz.com/darts-dice-coins/
     * @param n 原始权重数组长度
     * @param weighted_list 权重数组
     * @param m 采样数量
     * @param result_list 采样结果数组
     */
    static void weighted_random_sample_alias_method_vose(int n, const double* weighted_list, int m, int* result_list);

    /**
     * 蓄水池抽样算法（适用于未知长度的序列、也适用流处理的情况）
     * 算法复杂度：O(n)
     * @param m 抽样数量
     * @param result_list 抽样结果
     * @param flow_list 任意长度的序列，实际上流序列是任意
     * @param n 序列的长度（实际应该不存在长度，因为序列的长度是任意长度，无法提前知道，这里只是为了方便计算）
     */
    static void reservoir_sampling(int m, int *result_list, const int* flow_list, int n);

    // 加权抽样算法-蓄水池版本（适合在线流处理）
    // 论文：Weighted Random Sampling (2005; Efraimidis, Spirakis) Pavlos S. Efraimidis, Democritus University of Thrace, utopia.duth.gr/˜pefraimi Paul G. Spirakis, Research Academic Computer Technology Institute, www.cti.gr
    // 论文地址：https://utopia.duth.gr/~pefraimi/research/data/2007EncOfAlg.pdf
    // 算法证明的论文地址：https://www.sciencedirect.com/science/article/abs/pii/S002001900500298X
    // https://lotabout.me/2018/Weighted-Random-Sampling/
};

#endif //RANDOM_SAMPLING_H
