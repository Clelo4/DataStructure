//
// Created by jack on 7/9/23.
//

#include <ctime>
#include <cstdlib>
#include "RandomSampling.h"

void RandomSampling::weighted_random_sampling(int n, int *weighted_list, int m, int *result_list) {
    int total_weight = 0;
    // 由于使用整数表示权重，所以需要统计所有权重总和
    for (int i = 0; i < n; ++i) total_weight += weighted_list[i];

    srand(time(nullptr));
    for (int i = 0; i < m; ++i) {
        int k = (rand() % total_weight) + 1;

        // 选中
        int prefix_sum = 0;
        int j = -1;
        while (prefix_sum < k) {
            j++;
            while (weighted_list[j] == 0) j++;
            prefix_sum += weighted_list[j];
        }
        total_weight -= weighted_list[j];
        result_list[i] = j;
        weighted_list[j] = 0;
    }
}

void RandomSampling::reservoir_sampling(int k, int *result_list, const int *flow_list, int flow_len) {
    srand(time(nullptr));

    int i = 0;
    for (; i < k; ++i) {
        // 在每次循环中，i被保留下来的概率是100%
        result_list[i] = flow_list[i];
    }

    for (; i < flow_len; ++i) {
        // 在每次循环中，第i个元素和蓄水池的元素被保留下来的概率都是k/i

        int n = rand() % i;
        if (n < k) {
            result_list[n] = flow_list[i];
        }

        // 分析：
        // 对于新加入的元素i：被保留的概率是k/i，被丢弃的概率是(i-k)/i
        // 对于蓄水池的元素，被保留的概率是k/(i-1) * ((i-k)/i + k/i * ((k - 1)/k)) =
        // k/(i-1) * ((i-k)/i + (k-1)/i) =
        // k/(i-1) * (i-1)/i =
        // k/i
    }
}
