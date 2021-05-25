#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sort.h"

#define isPrint 0

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

int checkSorted(int arr[], int length) {
  if (!arr || length <= 1) return -1;
  int start = 0;
  while (start < length - 1) {
    if (arr[start] > arr[start + 1]) break;
    start++;
  }
  if (start == length - 1) return 1;
  else return 0;
}

void print(int arr[], int length) {
  if (!isPrint) return;
  for (int i = 0; i < length; i++) {
    printf(" %d", arr[i]);
  }
  printf("\n");
}

int main(void) {
  int len = 200;
  int* arr = NULL;
    
  arr = getRandomArr(len);
  heapSort(arr, len);
  if (checkSorted(arr, len) == 1) {
    printf("heapSort  测试通过!\n");
  } else {
    printf("heapSort  测试不通过!\n");
  }
  print(arr, len);
  free(arr);

  // test quicksort
  arr = getRandomArr(len);
  quicksort(arr, 0, len - 1);
  if (checkSorted(arr, len) == 1) {
    printf("quicksort  测试通过!\n");
  } else {
    printf("quicksort  测试不通过!\n");
  }
  print(arr, len);
  free(arr);

  arr = getRandomArr(len);
  insertSort(arr, len);
  if (checkSorted(arr, len) == 1) {
    printf("insertSort  测试通过!\n");
  } else {
    printf("insertSort  测试不通过!\n");
  }
  print(arr, len);
  free(arr);

  arr = getRandomArr(len);
  bubbleSort(arr, len);
  if (checkSorted(arr, len) == 1) {
    printf("bubbleSort  测试通过!\n");
  } else {
    printf("bubbleSort  测试不通过!\n");
  }
  print(arr, len);
  free(arr);

  arr = getRandomArr(len);
  selectSort(arr, len);
  if (checkSorted(arr, len) == 1) {
    printf("selectSort  测试通过!\n");
  } else {
    printf("selectSort  测试不通过!\n");
  }
  print(arr, len);
  free(arr);
  
  arr = getRandomArr(len);
  print(arr, len);
  mergetSortV2(arr, len);
  if (checkSorted(arr, len) == 1) {
    printf("mergeSort  测试通过!\n");
  } else {
    printf("mergeSort  测试不通过!\n");
  }
  print(arr, len);
  free(arr);
  
  arr = getRandomArr(len);
  shellSort(arr, len);
  if (checkSorted(arr, len) == 1) {
    printf("shellSort  测试通过!\n");
  } else {
    printf("shellSort  测试不通过!\n");
  }
  print(arr, len);
  free(arr);
  
  arr = getRandomArr(len);
  countingSort(arr, len);
  if (checkSorted(arr, len) == 1) {
    printf("countingSort  测试通过!\n");
  } else {
    printf("countingSort  测试不通过!\n");
  }
  print(arr, len);
  free(arr);
  
  arr = getRandomArr(len);
  bucketSort(arr, len);
  if (checkSorted(arr, len) == 1) {
    printf("bucketSort  测试通过!\n");
  } else {
    printf("bucketSort  测试不通过!\n");
  }
  print(arr, len);
  free(arr);
  
  arr = getRandomArr(len);
  radixSort(arr, len);
  if (checkSorted(arr, len) == 1) {
    printf("radixSort  测试通过!\n");
  } else {
    printf("radixSort  测试不通过!\n");
  }
  print(arr, len);
  free(arr);

  return 0;
}
