//
// Created by jack on 18/9/23.
//

#ifndef BINARY_SEARCH_UNIFORMBINARYSEARCH_H
#define BINARY_SEARCH_UNIFORMBINARYSEARCH_H

#include <ctime>
#include <cstdlib>
#include <cassert>
#include <iterator>
#include <algorithm>

const int LOGN = 10;

/**
 * https://en.wikipedia.org/wiki/Uniform_binary_search
 * invented by Donald Knuth
 * 算法复杂度：O(n * log(n))
 */
class UniformBinarySearch {
public:
    UniformBinarySearch(int n, int* list);
    int search(int key);
    static void test() {
        const int n = 100;
        int list[n] = {};
        srand(time(nullptr));
        for (int i = 0; i < n; ++i) {
            list[i] = rand() % (n * 3);
        }
        std::sort(std::begin(list), std::end(list));
        UniformBinarySearch uniformBinarySearch(n, list);
        for (int i = 1; i < n; ++i) {
            int key = list[i];
            int res = uniformBinarySearch.search(key);
            assert(list[res] == key);
        }
    }
private:
    int n;
    int* list;
    int delta[LOGN] = {};
    void make_delta();
};


#endif //BINARY_SEARCH_UNIFORMBINARYSEARCH_H
