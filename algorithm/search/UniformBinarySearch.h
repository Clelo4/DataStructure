//
// Created by jack on 18/9/23.
//

#ifndef BINARY_SEARCH_UNIFORMBINARYSEARCH_H
#define BINARY_SEARCH_UNIFORMBINARYSEARCH_H

const int LOGN = 10;

class UniformBinarySearch {
public:
    UniformBinarySearch(int n, int* list);
    int search(int key);
private:
    int n;
    int* list;
    int delta[LOGN] = {};
    void make_delta();
};


#endif //BINARY_SEARCH_UNIFORMBINARYSEARCH_H
