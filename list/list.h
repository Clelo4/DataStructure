//
//  list.h
//  data_structure
//
//  Created by jack on 2020/12/8.
//

#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdlib.h>

struct __list_node;
typedef struct __list_node* ListNode;
struct __list_node {
    ListNode pre;
    ListNode next;
    int data;
};

struct __list {
    ListNode start; // 哨兵节点
    ListNode end; // 哨兵节点
};

typedef struct __list* List;

// 初始化一个空线性表L;
List list_new(void);
// 根据位序K，返回相应的元素
ListNode list_find_kth(int k, List L);
// 在线性表L中查找X的第一次出现位置
int list_find(int x, List L);
// 在位序i前插入一个新元素x；
void list_insert(int x, List L);
// 删除指定位序的元素
void list_delete(int i, List L);
// 返回线性表L的长度
int list_length(List L);
// 删除整个List
void list_free(List);

#endif /* list_h */
