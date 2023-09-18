//
// Created by jack on 18/9/23.
//

#ifndef BINARY_SEARCH_EXPONENTIALSEARCH_H
#define BINARY_SEARCH_EXPONENTIALSEARCH_H


#include <ctime>
#include <cstdlib>
#include <algorithm>

class ExponentialSearch {
public:
    int n;
    int* list;
    explicit ExponentialSearch(int n, int* list);
    int search(int key);
    int searchTwo(int key);

    static void test() {
        const int n = 10000;
        int list[n] = {};
        srand(time(nullptr));

        for (int i = 0; i < n; ++i) {
            list[i] = i * i + n * 3;
        }
        std::sort(std::begin(list), std::end(list));
        ExponentialSearch exponentialSearch(n, list);
        for (int i = 62; i < 100; ++i) {
            int key = list[i];
            int res = exponentialSearch.search(key);
            assert(list[res] == key);
        }
    }
    static void testTwo() {
        const int n = 100000;
        int list[n] = {};
        srand(time(nullptr));

        for (int i = 0; i < n; ++i) {
            int res = rand() % (n + 1851);
            if (i > 1) {
                res +=  rand() % i;
                if (i % 3) res += list[rand() % i];
                else if (i % 2) res += rand() % i - rand() % i;
                else if (i % 4) res += list[rand() % i];
                else if (i % 5) res -= list[rand() % i] + rand() % i;
                else if (i % 7) res += list[rand() % i];
                else if (i % 6) res -= list[rand() % i] + rand() % i;
            }
            list[i] = res;
        }
        std::sort(std::begin(list), std::end(list));
        ExponentialSearch exponentialSearch(n, list);
        for (int i = 0; i < n; ++i) {
            int key = list[i];
            int res = exponentialSearch.searchTwo(key);
            assert(list[res] == key);
        }
    }
};


#endif //BINARY_SEARCH_EXPONENTIAL-SEARCH_H
