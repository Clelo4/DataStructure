#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "RedBlackTree.h"

int main() {
    RedBlackTree *tree = new RedBlackTree();
    int test_data[] = { 1, 2 , 3, 4, 5, 6, 7, 8, 9 };
    int len = sizeof(test_data) / sizeof(int);
    for (int i = 0; i < len; ++i) {
        tree->insert_node(tree->createNode(test_data[i]));
    }
    tree->delete_node(tree->search_key(5));
    assert(tree->search_key(6)->color == BLACK);
    tree->delete_node(tree->search_key(2));
    assert(tree->search_key(1)->color == RED);
    assert(tree->binary_tree_height() == 4);
    free(tree);
    printf("RedBlackTree test pass.\n");
    return 0;
}
