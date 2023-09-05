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
