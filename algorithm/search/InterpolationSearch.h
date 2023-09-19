//
// Created by jack on 20/9/23.
//

#ifndef BINARY_SEARCH_INTERPOLATIONSEARCH_H
#define BINARY_SEARCH_INTERPOLATIONSEARCH_H


#include <ctime>
#include <cstdlib>
#include <algorithm>

class InterpolationSearch {
private:
    int size;
    int* list;
    explicit InterpolationSearch(int size, int* list);
public:
    int search(int key);
    static void testTwo() {
        const int n = 100000;
        int list[n] = {};

        // 产生随机数
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
        InterpolationSearch interpolationSearch(n, list);
        for (int i = 0; i < n; ++i) {
            int key = list[i];
            int res = interpolationSearch.search(key);
            assert(list[res] == key);
        }
    }
};


#endif //BINARY_SEARCH_INTERPOLATIONSEARCH_H
