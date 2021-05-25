#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "max_heap.h"

int* getRandomArr(num) {
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

int checkMaxHeap(int arr[], int len) {
  int isOk = 1;
  for (int i = 1; i <= len; i++) {
    int left = i * 2; int right = i * 2 + 1;
    if (left <= len) {
      if (arr[i] < arr[left]) {
        isOk = 0;
        break;
      }
    }
    if (right <= len) {
      if (arr[i] < arr[right]) {
        isOk = 0;
        break;
      }
    }
  }
  return isOk;
}


int main(void) {
  int size = 100;
  int* arr = getRandomArr(size);
  print(arr, size);
  MaxHeap heap = create_max_heap(size);
  for (int i = 0; i < size; i++) {
    max_heap_insert(heap, arr[i]);
  }
  // printf("\n\n\n%d\n\n\n", checkMaxHeap(heap->arr, size));

  printf("\n\n");
  int last = -1;
  for (int i = 0; i < size; i++) {
    int result = max_heap_delete(heap);
    printf("%d ", result);
    if (last != -1 && result > last) {
      printf("max_heap error");
    }
    last = result;
  }

  free(arr);
  delete_max_heap(heap);
  return 0;
}
