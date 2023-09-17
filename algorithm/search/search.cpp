//
// Created by jack on 17/9/23.
//

#include <cmath>
#include "search.h"

int search::binary_search_base_one(int len, int *list, int key) {
    int left = 0;
    int right = len - 1;
    while (left <= right) {
        // 向下取整
        int mid = floor(((double) left + (double) right) / 2);
        if (list[mid] == key) return mid;
        else if (list[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int search::binary_search_base_tow(int len, int *list, int key) {
    int left = 0;
    int right = len - 1;
    while (left != right) {
        // 向上取整
        int mid = ceil(((double) left + (double) right) / 2);
        if (list[mid] > key) {
            right = mid - 1;
        } else {
            left = mid;
        }
    }
    if (list[left] == key) return left;
    return -1;
}
