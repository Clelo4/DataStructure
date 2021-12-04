#include <stdlib.h>
#include <stdio.h>
#include "min_heap.h"

MinHeap create_min_heap(int capacity) {
  if (capacity <= 0)
    return NULL;
  MinHeap heap = calloc(1, sizeof(struct _MinHeap));
  heap->arr = calloc(capacity + 1, sizeof(int));
  heap->size = 0;
  heap->capacity = capacity;
  return heap;
}

void delete_min_heap(MinHeap heap) {
  if (!heap)
    return;
  heap->size = heap->capacity = 0;
  free(heap->arr);
  free(heap);
}

void min_heap_insert(MinHeap heap, int x) {
  if (heap->size >= heap->capacity) {
    printf("heap is full.");
    return;
  }
  heap->arr[++heap->size] = x;
  int i = heap->size;
  for (; i > 1 && heap->arr[i / 2] > x; i /= 2) {
    heap->arr[i] = heap->arr[i / 2];
  }
  heap->arr[i] = x;
}

int min_heap_delete(MinHeap heap) {
  if (!heap || !heap->arr || heap->size <= 0 || heap->capacity <= 0) {
    exit(EXIT_FAILURE);
  }
  int min = heap->arr[1];
  heap->arr[1] = heap->arr[heap->size--];
  int father = 1;
  int son;
  int tmp = heap->arr[1];
  for (; father * 2 <= heap->size;) {
    son = father * 2;
    if (son < heap->size && heap->arr[son] > heap->arr[son + 1])
      son++;
    if (heap->arr[son] < tmp) {
      heap->arr[father] = heap->arr[son];
      father = son;
    } else
      break;
  }
  heap->arr[father] = tmp;
  return min;
}
