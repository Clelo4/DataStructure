//
//  queue.c
//  data_structure
//
//  Created by jack on 2020/12/9.
//

#include "queue.h"

Queue queue_new(int MaxSize) {
  Queue q = calloc(1, sizeof(struct queue));
  q->length = 0;
  q->maxSize = MaxSize;
  q->first = NULL;
  q->last = NULL;
  return q;
};
int queue_is_full(Queue q) { return q->length == q->maxSize; }
void queue_add(Queue q, int x) {
  Queue_Node newTarget = calloc(1, sizeof(struct __queue_node));
  newTarget->data = x;
  newTarget->next = NULL;
  if (q->length == 0) {
    q->first = q->last = newTarget;
  } else {
    q->last->next = newTarget;
    q->last = newTarget;
  }
  q->length++;
  return;
}
int queue_is_empty(Queue q) { return q->length == 0; }
int queue_length(Queue q) { return q->length; }
int queue_delete(Queue q) {
  if (q->length < 1)
    exit(EXIT_FAILURE);
  Queue_Node target = q->first;
  if (q->length == 1) {
    q->first = q->last = NULL;
  } else {
    q->first = q->first->next;
  }
  int result = target->data;
  free(target);
  target = NULL;
  q->length--;
  return result;
}
// 删除整个队列
void queue_free(Queue q) {
  Queue_Node start = q->first;
  Queue_Node target = NULL;
  while (start) {
    target = start;
    start = start->next;
    free(target);
  }
  free(q);
  return;
}
