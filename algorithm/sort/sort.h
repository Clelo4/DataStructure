#ifndef __SORT_H
#define __SORT_H

const static int BUCKET_CAPACITY = 1000;

void quicksort(int arr[], int begin, int end);
void insertSort(int arr[], int length);
void bubbleSort(int arr[], int length);
void selectSort(int arr[], int length);
void mergeSort(int arr[], int begin, int end);
void shellSort(int arr[], int length);
void heapSort(int arr[], int length);
void countingSort(int arr[], int length);
void bucketSort(int arr[], int length);
void radixSort(int arr[], int length);
void mergetSortV2(int arr[], int length);

#endif
