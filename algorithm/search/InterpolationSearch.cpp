//
// Created by jack on 20/9/23.
//

#include "InterpolationSearch.h"

InterpolationSearch::InterpolationSearch(int size, int *list): size(size), list(list) {
}

int InterpolationSearch::search(int key) {
    int low = 0;
    int hight = size - 1;
    int mid = 0;

    while ((list[hight] != list[low]) && (key >= list[low]) && (key <= list[hight])) {
        mid = low + (key - list[low]) * (hight - low) / (list[hight] - list[low]);

        if (list[mid] == key) return mid;
        else if (list[mid] < key) {
            low = mid + 1;
        } else {
            low = mid - 1;
        }
    }
    if (list[low] == key) return low;

    return -1;
}
