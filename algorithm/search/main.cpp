#include <iostream>
#include <algorithm>
#include "search.h"

int main() {
    srand(time(nullptr));
    int list[100] = {};
    for (int i = 0; i < 100; i++) {
        list[i] = rand() % 1000;
    }
    std::sort(std::begin(list), std::end(list));

    int key = list[51];
    assert(Search::binary_search_base_one(100, list, key) == 51);
    assert(Search::binary_search_base_two(100, list, key) == 51);
    return 0;
}
