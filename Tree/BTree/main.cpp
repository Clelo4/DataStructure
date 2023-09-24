#include <iostream>
#include "BTree.h"
#include "BPlusTree.h"
#include "BStarTree.h"

int main() {
    BTree::test();
    BPlusTree::test();
    BStarTree::test();
    return 0;
}
