#include <stdio.h>
#include <stdlib.h>
#include "max_heap.h"

MaxHeap create_max_heap(int capacity) {
  if (capacity <= 0)
    return NULL;
  MaxHeap heap = calloc(1, sizeof(struct _MaxHeap));
  heap->size = 0;
  heap->capacity = capacity;
  heap->arr = calloc(capacity + 1, sizeof(int));
  return heap;
}
void delete_max_heap(MaxHeap heap) {
  if (!heap || !heap->arr)
    return;
  heap->size = heap->capacity = 0;
  free(heap->arr);
}
void max_heap_insert(MaxHeap heap, int x) {
  if (heap->size >= heap->capacity) {
    printf("MaxHeap is Full.");
    return;
  }
  heap->arr[++heap->size] = x;
  int i = heap->size;
  for (; i > 1 && heap->arr[i / 2] < x; i /= 2) {
    heap->arr[i] = heap->arr[i / 2];
  }
  heap->arr[i] = x;
}
int max_heap_delete(MaxHeap heap) {
  int max = heap->arr[1];
  int tmp = heap->arr[heap->size];
  int i = 1;
  for (; i * 2 <= heap->size;) {
    int son = i * 2;
    if (son < heap->size && heap->arr[son] < heap->arr[son + 1])
      son++;
    if (heap->arr[son] > tmp) {
      heap->arr[i] = heap->arr[son];
      i = son;
    } else
      break;
  }
  heap->arr[i] = tmp;
  --heap->size;
  return max;
}