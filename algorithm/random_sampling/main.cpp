//
// Created by jack on 5/9/23.
//
#include <iostream>
#include "RandomSampling.h"

void print_list(const char* describe, const int *list, int len) {
    std::cout << describe;
    for (int i = 0; i < len; ++i) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    const int origin_list[] = {100,2,23,35,56,56,76,88};
    const int len = sizeof(origin_list) / sizeof(int);
    int* result_list = new int[len];
    int* second_origin_list = new int[len];

    print_list("origin: ", origin_list, len);

    memcpy(second_origin_list, origin_list, sizeof(int) * len);
    RandomSampling::weighted_random_sampling(len, second_origin_list, 3, result_list);
    print_list("weighted_random_sampling: ", result_list, 3);

    RandomSampling::reservoir_sampling(3, result_list, origin_list, len);
    print_list("reservoir_sampling: ", result_list, 3);

    RandomSampling::weighted_random_sampling_base(len, origin_list, len / 2, result_list);
    print_list("weighted_random_sampling_base: ", result_list, len / 2);

    RandomSampling::weighted_random_sampling_bst(len, origin_list, len / 2 + 1, result_list);
    print_list("weighted_random_sampling_bst: ", result_list, len / 2 + 1);

    delete []result_list;
    delete []second_origin_list;
    return 0;
}