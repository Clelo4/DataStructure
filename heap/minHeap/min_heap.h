#ifndef _MIN_HEAP_H
#define _MIN_HEAP_H

typedef struct _MinHeap* MinHeap;
struct _MinHeap {
  int* arr;
  int size;
  int capacity;  
};

MinHeap create_min_heap(int);
void delete_min_heap(MinHeap);
void min_heap_insert(MinHeap, int);
int min_heap_delete(MinHeap);

#endif
