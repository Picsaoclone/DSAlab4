#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

// Insertion Sort for small arrays
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge Sort for large arrays
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
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

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Wrapper for mergeSort to match measureSortTime's expected function signature
void mergeSortWrapper(int arr[], int n) {
    mergeSort(arr, 0, n - 1);
}

// Hybrid Sort that switches between Merge Sort and Insertion Sort
void hybridSort(int arr[], int n) {
    // Threshold for using Insertion Sort (arrays of size <= 10)
    if (n <= 10) {
        insertionSort(arr, n);
    } else {
        mergeSort(arr, 0, n - 1);
    }
}

// Function to generate random array
void generateRandomArray(int arr[], int n, int min = 1, int max = 10000) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + rand() % (max - min + 1);
    }
}

// Function to measure the execution time of the sorting algorithm
long long measureSortTime(void (*sortFunc)(int[], int), int arr[], int n, const string& sortName) {
    auto start = high_resolution_clock::now();
    sortFunc(arr, n);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << sortName << " time for " << n << " elements: " << duration << " microseconds" << endl;
    return duration;
}

int main() {
    srand(time(0)); // Seed for random number generation

    // Array sizes to test
    int sizes[] = {10, 50, 200};  // Sizes of arrays for testing
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    // Compare the performance of Hybrid Sort with Merge Sort
    for (int i = 0; i < numSizes; i++) {
        int n = sizes[i];

        // Generate random arrays
        int* arr = new int[n];
        generateRandomArray(arr, n); // Generate random array

        int* arrCopy = new int[n]; // Copy array for each sort
        copy(arr, arr + n, arrCopy);

        cout << "\nTesting Hybrid Sort for " << n << " elements:" << endl;
        long long hybridTime = measureSortTime(hybridSort, arrCopy, n, "Hybrid Sort");

        // Reset the array and measure time for Merge Sort using the wrapper
        copy(arr, arr + n, arrCopy);
        cout << "\nTesting Merge Sort for " << n << " elements:" << endl;
        long long mergeTime = measureSortTime(mergeSortWrapper, arrCopy, n, "Merge Sort");

        delete[] arr;
        delete[] arrCopy;
    }

    return 0;
}

