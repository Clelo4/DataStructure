#include "LRU_list.h"
#include <stdlib.h>

LRU_LIST* create_LRU_List(int capacity) {
  if (capacity < 1) return NULL;
  LRU_LIST* list = malloc(sizeof(LRU_LIST));
  list->capacity = capacity;
  list->size = 0;
  list->first = list->last = NULL;
  return list;
}
int LRU_List_insert(LRU_LIST* list, int data) {
  if (list == NULL) return -1;
  if (list->size >= list->capacity) {
    ListNode* delete_target = list->last;
    list->last = list->last->pre;
    list->last->next = NULL;
    free(delete_target);
  }
  ListNode* newNode = malloc(sizeof(ListNode));
  newNode->pre = NULL;
  newNode->data = data;
  newNode->next = list->first;
  list->first->pre = newNode;
  list->first = newNode;
  return 0;
}
int LRU_List_delete(LRU_LIST* list, int data) {
  if (list == NULL) return NULL;
  ListNode* target = list->first;
  while (target) {
    if (data == target->data) {
      break;
    } else {
      target = target->next;
    }
  }
  if (target == NULL) return -1;
  ListNode* t_pre = target->pre;
  ListNode* t_next = target->next;
  if (t_pre != NULL) t_pre->next = t_next;
  if (t_next != NULL) t_next->pre = t_pre;
  if (list->first == target) {
    list->first = target->next;
  }
  if (list->last == target) {
    list->last = target->pre;
  }
  free(target);
  return 0;
}
ListNode* LRU_List_search(LRU_LIST* list, int data) {
  if (list == NULL) return NULL;
  ListNode* target = list->first;
  while (target) {
    if (data == target->data) {
      break;
    } else {
      target = target->next;
    }
  }
  if (target == NULL) return NULL;
  if (list->first == target) {
    return target;
  }
  ListNode* t_pre = target->pre;
  ListNode* t_next = target->next;
  if (t_pre != NULL) t_pre->next = t_next;
  if (t_next != NULL) t_next->pre = t_pre;
  if (list->last == target) {
    list->last = target->pre;
  }
  target->next = list->first;
  list->first->pre = target;
  target->pre = NULL;
  list->first = target;
  return target;
}
int delete_LRU_List(LRU_LIST* list) {
  if (list == NULL) return -1;
  else {
    list->size = list->capacity = 0;
    ListNode* target = list->first;
    ListNode* temp = NULL;
    while (target)
    {
      temp = target;
      target = target->next;
      free(temp);
    }
    free(list);
    return 0;
  }
}