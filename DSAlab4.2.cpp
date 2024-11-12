// 22520468
// Nguyen Huy Hoang
// Exercise 02

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
long long measureSortTime(void (*sortFunc)(T[], int), T arr[], int n, const string& sortName) {
    auto start = high_resolution_clock::now();
    sortFunc(arr, n);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << sortName << " time for " << n << " elements: " << duration << " microseconds" << endl;
    return duration;
}

// Function to copy arrays
template <typename T>
void copyArray(T source[], T dest[], int n) {
    for (int i = 0; i < n; i++) dest[i] = source[i];
}

int main() {
    srand(time(0)); // Seed for random number generation

    // Define array sizes
    int sizes[] = {100, 1000, 10000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    // Loop over each size
    for (int i = 0; i < numSizes; i++) {
        int n = sizes[i];
        int* arr = new int[n];
        generateRandomArray(arr, n); // Generate random array

        int* arrCopy = new int[n]; // Copy array for each sort

        cout << "\nSorting " << n << " elements:\n";

        // Measure and record times for each sorting algorithm
        copyArray(arr, arrCopy, n);
        long long bubbleTime = measureSortTime(bubbleSort, arrCopy, n, "Bubble Sort");

        copyArray(arr, arrCopy, n);
        long long insertionTime = measureSortTime(insertionSort, arrCopy, n, "Insertion Sort");

        copyArray(arr, arrCopy, n);
        long long selectionTime = measureSortTime(selectionSort, arrCopy, n, "Selection Sort");

        delete[] arr;
        delete[] arrCopy;

        // Record the times for plotting purposes (you may want to store these in a file or array)
        cout << "Results for " << n << " elements:\n";
        cout << "Bubble Sort: " << bubbleTime << " µs\n";
        cout << "Insertion Sort: " << insertionTime << " µs\n";
        cout << "Selection Sort: " << selectionTime << " µs\n";
    }

    return 0;
}
