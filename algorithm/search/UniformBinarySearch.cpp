//
// Created by jack on 18/9/23.
//

#include "UniformBinarySearch.h"

UniformBinarySearch::UniformBinarySearch(int n, int* list): n(n), list(list) {
    make_delta();
}

void UniformBinarySearch::make_delta() {
    int power = 1;
    int i = 0;
    do {
        int half = power;
        // 向上取整
        power <<= 1;
        delta[i] = (n + half) / power;
    } while (delta[i++] != 0);
}

int UniformBinarySearch::search(int key) {
    int i = delta[0] - 1;
    int d = 0;
    while (true) {
        if (list[i] == key) return i;
        if (delta[d] == 0) return -1;
        else {
            if (list[i] < key) {
                i += delta[++d];
            } else {
                i -= delta[++d];
            }
        }
    };
}
