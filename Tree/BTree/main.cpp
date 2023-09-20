#include <iostream>
#include "BTree.h"

int main() {

    BTree btree(6);
    for (int i = 1; i < 2000; i++) {
        btree.insert(i);
    }
    btree.remove(52);
    assert(btree.search(52) == nullptr);
    assert(btree.search(1) != nullptr);

    auto finded = btree.search(30);
    if (finded != nullptr) {
        for (auto key : finded->keys) {
            std::cout << key << " ";
        }
        std::cout << std::endl;
    }

    btree.search(30);
    for (int i = 200; i > 0; i--) {
        btree.remove(i % 2);
    }
    for (int i = 500; i < 700; i++) {
        btree.remove(i);
    }
    for (int i = 200; i > 0; i--) {
        assert(btree.search(i % 2) == nullptr);
    }
    for (int i = 500; i < 700; i++) {
        assert(btree.search(i) == nullptr);
    }
    assert(btree.search(1) == nullptr);
    assert(btree.search(2) == nullptr);
    return 0;
}
