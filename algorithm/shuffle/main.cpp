//
// Created by jack on 5/9/23.
//
#include <iostream>
#include "Shuffle.h"

void print_list(const char* describe, const int *list, int len) {
    std::cout << describe;
    for (int i = 0; i < len; ++i) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    const int origin_list[] = {1,2,234,35,546,56,76,8798};
    const int len = sizeof(origin_list) / sizeof(int);
    int* result_list = new int[len];
    int* second_origin_list = new int[len];

    print_list("origin: ", origin_list, len);

    Shuffle::fisher_yates_origin_shuffle(len, origin_list, result_list);
    print_list("fisher_yates_origin_shuffle: ", result_list, len);

    memcpy(result_list, origin_list, sizeof(int) * len);
    Shuffle::knuth_shuffle(len, result_list);
    print_list("knuth_shuffle: ", result_list, len);

    delete []result_list;
    delete []second_origin_list;
    return 0;
}