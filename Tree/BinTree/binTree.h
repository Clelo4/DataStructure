//
//  binTree.h
//  data_structure
//
//  Created by jack on 2020/12/10.
//

#ifndef binTree_h
#define binTree_h

#include <stdio.h>

typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
    int data;
    BinTree left;
    BinTree right;
};
// 先序遍历
void pre_order_traversal(BinTree);
// 中序遍历
void in_order_traversal(BinTree);
// 后序遍历
void post_order_traversal(BinTree);
// 层次遍历，从上到下，从左到右
void level_order_traversal(BinTree);

void bin_tree_insert_left(BinTree, BinTree);
void bin_tree_insert_right(BinTree, BinTree);
// 求树高度
int bin_tree_height(BinTree);

void bin_tree_free(BinTree);

#endif /* binTree_h */
