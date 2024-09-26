// 2. Implement divide and conquer based merge sort and quick sort algorithms and compare their performance for the same set of elements. 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Merge function for merge sort
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort function
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Function to swap two elements
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Partition function for quick sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Quick Sort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to generate random array
void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;  // Random numbers between 0 and 9999
    }
}

// Function to measure sorting time
double measureSortingTime(void (*sortFunction)(int[], int, int), int arr[], int n) {
    clock_t start, end;
    double cpu_time_used;

    int* arrCopy = (int*)malloc(n * sizeof(int));
    memcpy(arrCopy, arr, n * sizeof(int));

    start = clock();
    sortFunction(arrCopy, 0, n - 1);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    free(arrCopy);
    return cpu_time_used;
}

int main() {
    srand(time(NULL));

    int sizes[] = {1000, 5000, 10000, 50000, 100000};
    int num_sets = sizeof(sizes) / sizeof(sizes[0]);

    printf("Set\tSize\tMerge Sort Time\tQuick Sort Time\n");

    for (int i = 0; i < num_sets; i++) {
        int n = sizes[i];
        int* arr = (int*)malloc(n * sizeof(int));

        generateRandomArray(arr, n);

        double mergeSortTime = measureSortingTime(mergeSort, arr, n);
        double quickSortTime = measureSortingTime(quickSort, arr, n);

        printf("%d\t%d\t%.6f\t\t%.6f\n", i+1, n, mergeSortTime, quickSortTime);

        free(arr);
    }

    return 0;
}