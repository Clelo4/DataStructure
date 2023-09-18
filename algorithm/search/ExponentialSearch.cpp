//
// Created by jack on 18/9/23.
//

#include "ExponentialSearch.h"

ExponentialSearch::ExponentialSearch(int n, int *list): n(n), list(list) {

}

int ExponentialSearch::search(int key) {
    int cur = 0;
    if (list[0] == key) return 0;

    int bound = 1;
    // 需要确保list长度大于n的两倍，且list整个数组都是合法有序的
    while (cur < n && cur >= 0 && bound > 0) {
        if (list[cur] == key) return cur;
        if (list[cur] < key) {
            bound <<= 1;
            cur += bound;
        } else {
            bound >>= 1;
            cur -= bound;
        }
    }

    return -1;
}

int ExponentialSearch::searchTwo(int key) {
    int cur = 0;
    if (list[0] == key) return 0;

    // 确保key不会越届
    if (list[0] > key || list[n - 1] < key) return -1;

    int bound = 1;
    cur += bound;
    while (true) {
        if (list[cur] == key) return cur;
        if (list[cur] < key) {
            bound <<= 1;
            // 确保不会越界
            if (cur + bound >= n) {
                cur = (n - 1) - bound;
            }
            cur += bound;
        } else {
            break;
        }
    }

    // 此时cur位于末端，需要回退
    cur -= bound;
    while (bound > 0 && cur >= 0) {
        bound >>= 1;
        if (list[cur] == key) return cur;
        if (list[cur] < key) {
            cur += bound;
        } else {
            cur -= bound;
        }
    }

    return -1;
}
