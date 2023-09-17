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

int search::binary_search_base_two(int len, int *list, int key) {
    int left = 0;
    int right = len - 1;
    while (left < right) {
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

int search::binary_search_base_duplicate_left_most(int len, int *list, int key) {
    int left = 0, right = len - 1;
    while (left < right) {
        // 向下取整
        int mid = (left + right) / 2;
        if (list[mid] == key) {
            right = mid;
        } else if (list[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    if (list[left] == key) return left;
    return -1;
}

int search::binary_search_base_duplicate_right_most(int len, int *list, int key) {
    int left = 0, right = len - 1;
    while (left < right) {
        // 向上取整
        int mid = (left + right + 1) / 2;
        if (list[mid] == key) {
            left = mid;
        } else if (list[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    if (list[left] == key) return left;
    else return -1;
}

int search::binary_search_base_approximate_left_most(int len, int* list, int key) {
    int left = 0, right = len - 1;
    while (left < right) {
        // 向下取整
        int mid = (left + right) / 2;
        if (list[mid] == key) {
            right = mid;
        } else if (list[mid] < key) {
            if (mid + 1 < len) {
                if (list[mid + 1] <= key) {
                    left = mid + 1;
                    continue;
                }
                else {
                    right = left = mid;
                    break;
                }
            }
            exit(-1);
            // 代码运行不到这里
        } else {
            // 如果key小于所有元素，right = -1
            right = mid - 1;
        }
    }
    // 最终可能结果left == right、或则right < left
    if (right >= 0 && key < list[right]) return -1;
    return right; // right可能为-1
}

int search::binary_search_base_approximate_right_most(int len, int* list, int key) {
    int left = 0, right = len - 1;
    while (left < right) {
        // 向上取整
        int mid = (left + right + 1) / 2;
        if (list[mid] == key) {
            left = mid;
        } else if (list[mid] < key) {
            left = mid + 1;
        } else {
            if (list[mid - 1] >= key) {
                right = mid - 1;
                continue;
            } else {
                right = left = mid;
                break;
            }
            exit(-1);
            // 代码运行不到这里
        }
    }
    if (left >= len) return -1;
    return left;
}
