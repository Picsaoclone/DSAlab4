// 22520468
// Nguyen Huy Hoang
// Exercise 01

#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Bubble Sort
template <typename T>
void bubbleSort(T arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort
template <typename T>
void insertionSort(T arr[], int n) {
    for (int i = 1; i < n; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Selection Sort
template <typename T>
void selectionSort(T arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            T temp = arr[minIdx];
            arr[minIdx] = arr[i];
            arr[i] = temp;
        }
    }
}

// Function to generate random integers in an array
void generateRandomArray(int arr[], int n, int min = 1, int max = 10000) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + rand() % (max - min + 1);
    }
}

// Function to measure and print the execution time
template <typename T>
void measureSortTime(void (*sortFunc)(T[], int), T arr[], int n, const string& sortName) {
    auto start = high_resolution_clock::now();
    sortFunc(arr, n);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << sortName << " time: " << duration.count() << " microseconds" << endl;
}

// Function to copy arrays
template <typename T>
void copyArray(T source[], T dest[], int n) {
    for (int i = 0; i < n; i++) dest[i] = source[i];
}

int main() {
    const int size = 1000;
    int arr[size];
    generateRandomArray(arr, size); // Generate 1,000 random integers

    int arrCopy[size]; // Copy array for each sort

    cout << "Sorting 1,000 elements:\n";

    // Bubble Sort
    copyArray(arr, arrCopy, size);
    measureSortTime(bubbleSort, arrCopy, size, "Bubble Sort");

    // Insertion Sort
    copyArray(arr, arrCopy, size);
    measureSortTime(insertionSort, arrCopy, size, "Insertion Sort");

    // Selection Sort
    copyArray(arr, arrCopy, size);
    measureSortTime(selectionSort, arrCopy, size, "Selection Sort");

    return 0;
}
