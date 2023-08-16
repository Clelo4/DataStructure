#include <iostream>
#include "BTree.h"

int main() {

    BTree btree(10);
    btree.insert(1);
    btree.insert(2);
    btree.insert(3);
    btree.insert(4);
    btree.insert(5);
    for (int i = 1; i < 100; i++) {
        btree.insert(i * random());
    }
    auto finded = btree.search(52);
    if (finded != nullptr) {
        for (auto key : finded->keys) {
            std::cout << key << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
