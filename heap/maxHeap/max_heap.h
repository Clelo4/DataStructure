#ifndef __MAX_HEAP_H
#define __MAX_HEAP_H

typedef struct _MaxHeap* MaxHeap;
struct _MaxHeap {
  int *arr;
  int size;
  int capacity;
};

MaxHeap create_max_heap(int);
void max_heap_insert(MaxHeap, int);
int max_heap_delete(MaxHeap);
void delete_max_heap(MaxHeap);

#endif
