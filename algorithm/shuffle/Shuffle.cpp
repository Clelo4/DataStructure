//
// Created by jack on 5/9/23.
//

#include <cstdlib>
#include <cstring>
#include <ctime>
#include "Shuffle.h"

void Shuffle::fisher_yates_origin_shuffle(int len, const int *origin_list, int *result_list) {
    srand(time(nullptr));

    int n = len;
    bool* selected = new bool[len];
    memset(selected, 0, sizeof(bool) * len);
    for (; n > 0; --n) {
        int k = rand() % n + 1;

        int i = -1;
        while (k > 0) {
            i++;
            while(selected[i]) i++;
            k--;
        }
        selected[i] = true;

        result_list[n - 1] = origin_list[i];
    }

    delete []selected;
}

void Shuffle::knuth_shuffle(int len, int *origin_list) {
    srand(time(nullptr));

    for (int n = len; n > 0; n--) {
        int temp = origin_list[n - 1];
        int k = rand() % n;

        // swap k and n - 1
        origin_list[n - 1] = origin_list[k];
        origin_list[k] = temp;
    }
}

void Shuffle::weighted_random_sampling(int len, int *weighted_list, int *result_list) {
    int total_weight = 0;
    for (int i = 0; i < len; ++i) total_weight += weighted_list[i];

    srand(time(nullptr));
    for (int i = 0; i < len; ++i) {
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

void Shuffle::reservoir_sampling(int k, int *result_list, const int *flow_list, int flow_len) {
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
