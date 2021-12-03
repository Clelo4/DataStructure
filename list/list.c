//
//  list.c
//  data_structure
//
//  Created by jack on 2020/12/8.
//

#include "list.h"
#include <stdlib.h>

List list_new(void) {
    List a = NULL;
    a = calloc(1, sizeof(struct __list));
    a->start = calloc(1, sizeof(struct __list_node));
    a->end = calloc(1, sizeof(struct __list_node));
    // init
    a->start->pre = NULL; a->start->next = a->end;
    a->end->pre = a->start; a->end->next = NULL;
    return a;
}
ListNode list_find_kth(int k, List L) {
    if (k < 0) return NULL;
    ListNode target = L->start;
    for (int i = 0; i <= k; ++i) {
        if (target->next == L->end) {
            return NULL;
        } else {
            target = target->next;
        }
    }
    return target;
}
int list_find(int x, List L) {
    int index = 0;
    ListNode target = L->start->next;
    while(target != L->end) {
        if (target->data == x) {
            return index;
        }
        index++;
        target = target->next;
    }
    return -1;
}
void list_insert(int x, List L) {
    ListNode newNode = calloc(1, sizeof(struct __list_node));
    newNode->data = x; newNode->next = newNode->pre = NULL;
    ListNode target = L->start->next;
    while (target != L->end) {
        if (target->data <= x) {
            break;
        } else {
            target = target->next;
        }
    }
    newNode->pre = target->pre;
    target->pre->next = newNode;
    newNode->next = target;
    target->next->pre = newNode;
}
void list_delete(int x, List L) {
    ListNode target = L->start->next;
    ListNode temp = NULL;
    while (target != L->end) {
        if (target->data == x) {
            temp = target;
            target->pre->next = target->next;
            target->next->pre = target->pre;
            break;
        } else if (target->data < x) {
            target = target->next;
        } else {
            break;
        }
    }
    if (temp != NULL) {
        free(temp);
    }
}
int list_size(List L) {
    int size = 0;
    ListNode target = L->start;
    while(target->next != L->end) {
        target = target->next;
        size++;
    }
    return size;
}
void list_free(List L) {
    ListNode target = L->start;
    ListNode temp = NULL;
    while (target) {
        temp = target;
        target = target->next;
        free(temp);
    }
    free(L);
}
