#include <iostream>
#include <algorithm>
#include "search.h"

int main() {
    srand(time(nullptr));
    const int len = 11;
    int list[len] = {1, 1, 4,4,5,6,6,20,20,20, 21};
    std::sort(std::begin(list), std::end(list));

    int key = 1;
    assert(list[search::binary_search_base_one(len, list, key)] == key);
    assert(list[search::binary_search_base_two(len, list, key)] == key);

    assert(search::binary_search_base_duplicate_left_most(len, list, 5) == 4);
    assert(search::binary_search_base_duplicate_right_most(len, list, 5) == 4);
    assert(search::binary_search_base_duplicate_left_most(len, list, 20) == 7);
    assert(search::binary_search_base_duplicate_right_most(len, list, 20) == 9);
    assert(search::binary_search_base_duplicate_left_most(len, list, 1) == 0);
    assert(search::binary_search_base_duplicate_right_most(len, list, 1) == 1);

    assert(search::binary_search_base_approximate_left_most(len, list, 3) == 1);
    assert(search::binary_search_base_approximate_left_most(len, list, 21) == 10);
    assert(search::binary_search_base_approximate_left_most(len, list, 20) == 7);
    assert(search::binary_search_base_approximate_left_most(len, list, 0) == -1);
    assert(search::binary_search_base_approximate_left_most(len, list, 1) == 0);
    assert(search::binary_search_base_approximate_left_most(len, list, 4) == 2);
    assert(search::binary_search_base_approximate_left_most(len, list, 20) == 7);

    assert(search::binary_search_base_approximate_right_most(len, list, 3) == 2);
    assert(search::binary_search_base_approximate_right_most(len, list, 21) == 10);
    assert(search::binary_search_base_approximate_right_most(len, list, 20) == 9);
    assert(search::binary_search_base_approximate_right_most(len, list, 0) == 0);
    assert(search::binary_search_base_approximate_right_most(len, list, 1) == 1);
    assert(search::binary_search_base_approximate_right_most(len, list, 4) == 3);
    assert(search::binary_search_base_approximate_right_most(len, list, 20) == 9);
    assert(search::binary_search_base_approximate_right_most(len, list, -1) == 0);
    assert(search::binary_search_base_approximate_right_most(len, list, 22) == -1);
    assert(search::binary_search_base_approximate_right_most(len, list, 5) == 4);
}
