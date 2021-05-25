#include "sort.h"
#include <stdlib.h>

void swap(int arr[], int i, int j) {
  if (!arr) return;
  int tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}

void quicksort(int arr[], int begin, int end) {
  if (!arr) return;
  if (begin > end) return;
  int key = arr[end];
  int i = begin;
  int j = end;
  while (i < j) {
    while (i < j && arr[i] < key) {
      i++;
    }
    while (i < j && arr[j] >= key) {
      j--;
    }
    if (i < j) {
      swap(arr, i, j);
    }
  }
  arr[end] = arr[j];
  arr[j] = key;
  quicksort(arr, begin, i - 1);
  quicksort(arr, i + 1, end);
}

void quicksortV2(int arr[], int begin, int end) {
  if (!arr) return;
  if (begin > end) return;
  int key = arr[begin];
  int i = begin;
  int j = end;
  while (i < j) {
    while (i < j && arr[j] > key) {
      j--;
    }
    while (i < j && arr[i] <= key) {
      i++;
    }
    if (i < j) {
      swap(arr, i, j);
    }
  }
  arr[begin] = arr[i];
  arr[i] = key;
  quicksortV2(arr, begin, i - 1);
  quicksortV2(arr, i + 1, end);
}

void insertSort(int arr[], int length) {
  int sortedIndex = 0;
  int tmp, target;
  while (sortedIndex < length - 1) {
    target = sortedIndex + 1;
    for (tmp = arr[target]; target > 0 && tmp < arr[target - 1]; target--) {
      arr[target] = arr[target - 1];
    }
    arr[target] = tmp;
    sortedIndex++;
  }
}

void bubbleSort(int arr[], int length) {
  if (!arr || length <= 0) return;
  int sortedIndex = -1;
  while (sortedIndex < length - 1) {
    int flag = 0;
    // 从最后一个元素开始冒泡，直到target=sortedIndex + 1的位置，选出最小元素
    for (int target = length - 1; target > sortedIndex + 1; target--) {
      if (arr[target] < arr[target - 1]) {
        swap(arr, target, target - 1);
        flag = 1;
      }
    }
    sortedIndex++;
    if (!flag) break; // 没有冒泡，提前退出
  }
}

void selectSort(int arr[], int length) {
  if (!arr || length <= 0) return;
  int minIndex = 0;
  int sortedIndex = -1;
  while (sortedIndex < length - 1) {
    int target = length - 1;
    minIndex = target;
    // 从最后一个元素开始选出剩余未排序最小元素的index
    for (; target >= sortedIndex + 1; target--) {
      if (arr[target] < arr[minIndex]) minIndex = target;
    }
    swap(arr, sortedIndex + 1, minIndex);
    sortedIndex++;
  }
}

void _merge_sort(int arr[], int begin, int mid, int end) {
  if (!arr) return;
  int leftIndex = begin;
  int rightIndex = mid + 1;
  int* tmp = calloc(end - begin + 1, sizeof(int));
  int tmpIndex = 0;
  while (leftIndex <= mid && rightIndex <= end) {
    if (arr[leftIndex] <= arr[rightIndex]) tmp[tmpIndex++] = arr[leftIndex++];
    else tmp[tmpIndex++] = arr[rightIndex++];
  }
  while (leftIndex <= mid)
  {
    tmp[tmpIndex++] = arr[leftIndex++];
  }
  while (rightIndex <= end)
  {
    tmp[tmpIndex++] = arr[rightIndex++];
  }
  for (int i = 0; i < tmpIndex; i++) {
    arr[begin + i] = tmp[i];
  }
  free(tmp);
}

void mergeSort(int arr[], int begin, int end) {
  if (!arr) return;
  if (( end - begin) < 1) return;
  int mid = (end - begin) / 2 + begin;
  mergeSort(arr, begin, mid);
  mergeSort(arr, mid + 1, end);
  _merge_sort(arr, begin, mid, end);
}

void mergetSortV2(int arr[], int length) {
  if (length <= 1) return;
  int gap = 1;
  for (int gap = 1; gap < length; gap *= 2) {
    for (int i = 0; i < length; i += 2 * gap) {
      int begin = i;
      int mid = ((i + gap - 1) < length) ? (i + gap - 1) : (length - 1);
      int end = ((mid + gap) < length) ? (mid + gap) : (length - 1);
      _merge_sort(arr, begin, mid, end);
    }
  }
}

void shellSortV1(int arr[], int length) {
  if (!arr) return;
  if (length <= 1) return;
  int tmp;
  for (int gap = length >> 1; gap > 0; gap >>= 1) {
    for (int i = 0; i < gap; i++) {
      int sortedIndex = i;
      int target, insertIndex;
      while (sortedIndex + gap < length) {
        target = sortedIndex + gap;
        for (insertIndex = target; insertIndex - gap >= i && arr[target] < arr[insertIndex - gap]; insertIndex -= gap) {
        }
        // 移动target到insertIndex位置
        tmp = arr[target];
        while (target > insertIndex) {
          arr[target] = arr[target - gap];
          target -= gap;
        }
        arr[insertIndex] = tmp;
        sortedIndex += gap;
      }
    }
  }
}
void shellSortV2(int arr[], int lenght) {
  if (!arr && lenght < 2) return;
  int i, temp;
  int sortedIndex, target;
  for (int gap = lenght >> 1; gap > 0; gap >>= 1) {
    for (i = 0; i < gap; i++) {
      sortedIndex = i;
      while (sortedIndex + gap < lenght) {
        target = sortedIndex + gap;
        temp = arr[target];
        for (; target - gap >= i && temp < arr[target - gap]; target -= gap) {
          arr[target] = arr[target - gap];
        }
        arr[target] = temp;
        sortedIndex += gap;
      }
    }
  }
}
void shellSortV3(int arr[], int lenght) {
  if (!arr && lenght < 2) return;
  int i, temp;
  int target, gap;
  for (gap = lenght >> 1; gap > 0; gap >>= 1) {
    for (i = gap; i < lenght; i++) {
      target = i;
      temp = arr[i];
      for (target = i; target - gap >= 0 && temp < arr[target - gap]; target -= gap) {
        arr[target] = arr[target - gap];
      }
      arr[target] = temp;
    }
  }
}

void shellSort(int arr[], int lenght) {
  shellSortV3(arr, lenght);
}
void maxHeap(int arr[], int begin, int end) {
  if (!arr || begin >= end || begin < 0 || end < 0) return;
  int target = begin;
  int son = 2 * target + 1;
  int temp = arr[begin];
  while (son <= end) {
    if (son + 1 <= end && arr[son] < arr[son + 1]) son++;
    if (arr[son] > temp) {
      arr[target] = arr[son];
      target = son;
      son = target * 2 + 1;
    }
    else break;
  }
  arr[target] = temp;
}

void heapSort(int arr[], int length) {
  if (!arr || length < 1) return;
  int max;
  for (int i = length - 1; i >=0; i--) {
    maxHeap(arr, i, length - 1);
  }
  for (int i = length - 1; i > 0; i--) {
    max = arr[0];
    arr[0] = arr[i];
    arr[i] = max;
    maxHeap(arr, 0, i - 1);
  }
}

void countingSort(int arr[], int length) {
  if (!arr || length < 1) return;
  int min = arr[0], max = arr[0];
  for (int i = length - 1; i >= 0; i--) {
    if (arr[i] > max) max = arr[i];
    if (arr[i] < min) min = arr[i];
  }
  int* valueArrary = calloc(max - min + 1, sizeof(int));
  for (int i = 0; i < max - min + 1; i++) {
    valueArrary[i] = 0;
  }
  for (int i = 0; i < length; i++) {
    valueArrary[arr[i] - min] += 1;
  }
  int target = 0;
  for (int i = 0; i < max - min + 1; i++) {
    int num = valueArrary[i];
    while (num > 0) {
      arr[target++] = i + min;
      num--;
    }
  }
  free(valueArrary);
}

typedef struct _Node* Node;
struct _Node {
    int data;
    Node pre;
};
typedef struct _BucketNode* BucketNode;
struct _BucketNode {
    Node end;
};
// 插入排序
Node _insert(Node end, int data) {
    // end为已排序
    Node newNode = calloc(1, sizeof(struct _Node));
    newNode->pre = NULL; newNode->data = data;
    if (!end) {
        newNode->pre = NULL;
        return newNode;
    } else {
        Node target = end;
        Node last = NULL;
        while (target && data > target->data) {
            last = target;
            target = target->pre;
        }
        newNode->pre = target;
        if (last) {
            last->pre = newNode;
            return end;
        }
        else {
            return newNode;
        }
    }
}
void bucketSort(int arr[], int length) {
    int max = arr[0];
    for (int i = 0; i < length; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    int bucket_num = max / BUCKET_CAPACITY + 1;
    BucketNode buckets = calloc(bucket_num, sizeof(struct _BucketNode));
    // initial buckets
    for (int i = 0; i < bucket_num; i++) {
        buckets[i].end = NULL;
    }
    for (int i = 0; i < length; i++) {
        int index = arr[i] / BUCKET_CAPACITY;
        buckets[index].end = _insert(buckets[index].end, arr[i]);
    }
    int index = 0;
    for (int i = 0; i < bucket_num; i++) {
        Node target = buckets[i].end;
        while (target) {
            arr[index++] = target->data;
            target = target->pre;
        }
    }
    free(buckets);
}

int getRadix(int num, int radix) {
  int t = 10;
  while (radix-- > 0) {
    t *= 10;
  }
  return (num % t) / (t / 10);
}

typedef struct _radixNode* RadixNode;
struct _radixNode {
  int data;
  RadixNode next;
};
typedef struct _radixWrapperNode* RadixWrapperNode;
struct _radixWrapperNode {
  RadixNode start;
  RadixNode end;
};
void radixSort(int arr[], int length) {
  int max = arr[0];
  RadixWrapperNode wrapper = (RadixWrapperNode) calloc(10, sizeof(struct _radixWrapperNode));
  // 初始化
  for (int i = 0; i < 10; i++) {
    (wrapper + i)->end = (wrapper + i)->start = NULL;
  }
  // 获取数组的最大值
  for (int i = 0; i < length; i++) {
    if (arr[i] > max) max = arr[i];
  }
  // 获取数组元素的最大位数（从0开始计算）
  int max_radix = 1;
  while (max / 10 != 0) {
    max_radix++;
    max /= 10;
  }
  for (int i = 0; i < max_radix; i++) {
    for (int j = 0; j < length; j++) {
      int radix = getRadix(arr[j], i);
      RadixNode newNode = calloc(1, sizeof(struct _radixNode));
      newNode->next = NULL; newNode->data = arr[j];
      if ((wrapper + radix)->start == NULL) {
        (wrapper + radix)->start = (wrapper + radix)->end = newNode;
      } else {
        (wrapper + radix)->end->next = newNode;
        (wrapper + radix)->end = newNode;
      }
    }

    int index = 0;
    // 将wrapper的数据转移到arr中
    for (int m = 0; m < 10; m++) {
      RadixNode target = (wrapper + m)->start;
      RadixNode tmp;
      while (target) {
        arr[index++] = target->data;
        tmp = target;
        target = target->next;
        free(tmp);
      }
      (wrapper + m)->end = (wrapper + m)->start = NULL;
    }
  }
  free(wrapper);
}
