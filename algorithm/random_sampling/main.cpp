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
    const int origin_list[] = {80,170,23,35,56,56,76,88};
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

    RandomSampling::weighted_random_sampling_bst_no_put_back(len, origin_list, len, result_list);
    print_list("weighted_random_sampling_bst_no_put_back: ", result_list, len);

    RandomSampling::weighted_random_sampling_binary_search(len, origin_list, len / 2 + 1, result_list);
    print_list("weighted_random_sampling_binary_search: ", result_list, len / 2 + 1);

    int total = 0;
    for (int i : origin_list) total += i;
    double double_origin_list[len];
    for (int i = 0; i < len; i++) {
        double_origin_list[i] = (double) origin_list[i] / total;
    }
    RandomSampling::weighted_random_sample_alias_method_navie(len, double_origin_list, len, result_list);
    print_list("weighted_random_sample_alias_method_navie: ", result_list, len);

    RandomSampling::weighted_random_sample_alias_method_vose(len, double_origin_list, len, result_list);
    print_list("weighted_random_sample_alias_method_vose: ", result_list, len);

    delete []result_list;
    delete []second_origin_list;
    return 0;
}