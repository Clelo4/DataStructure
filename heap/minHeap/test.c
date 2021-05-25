#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "min_heap.h"

int* getRandomArr(int num) {
  srand((unsigned) time(NULL));
  int* arr = calloc(num, sizeof(int));
  for (int i = 0; i < num; i++) {
    arr[i] = i + 1;
  }
  for (int i = num - 1; i > 1; i--) {
    int randomNum = rand() % (i - 1);
    int tmp = arr[i];
    arr[i] = arr[arr[randomNum]]; 
    arr[arr[randomNum]] = tmp;
  }
  return arr;
}

void print(int arr[], int length) {
  printf("\n");
  for (int i = 0; i < length; i++) {
    printf(" %d", arr[i]);
  }
  printf("\n");
}

int main(void) {
  int size = 100;
  int* arr = getRandomArr(size);
  print(arr, size);
  MinHeap heap = create_min_heap(size);
  for (int i = 0; i < size; i++) {
    min_heap_insert(heap, arr[i]);
  }

  printf("\n\n");
  int last = -1;
  for (int i = 0; i < size; i++) {
    int result = min_heap_delete(heap);
    printf("%d ", result);
    if (last != -1 && result < last) {
      printf("min_heap error");
    }
    last = result;
  }

  free(arr);
  delete_min_heap(heap);
  return 0;
}
