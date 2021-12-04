#ifndef _LRU_LIST_H
#define _LRU_LIST_H

typedef struct {
  ListNode *pre;
  ListNode *next;
  int data;
} ListNode;
typedef struct {
  int capacity;
  int size;
  ListNode *first;
  ListNode *last;
} LRU_LIST;

LRU_LIST *create_LRU_List(int capacity);
int LRU_List_insert(LRU_LIST *list, int data);
int LRU_List_delete(LRU_LIST *list, int data);
ListNode *LRU_List_search(LRU_LIST *list, int data);
int delete_LRU_List(LRU_LIST *list);

#endif