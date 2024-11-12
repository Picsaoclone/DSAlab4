// 22520468
// Nguyen Huy Hoang
// Exercise 08

#include <iostream>
#include <chrono>
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

// Partition function for Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // pivot element
    int i = low - 1;  // index of smaller element
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);  // Recursively sort left subarray
        quickSort(arr, pi + 1, high); // Recursively sort right subarray
    }
}

// Hybrid Sort using Quick Sort for large subarrays and Insertion Sort for small subarrays
void hybridSort(int arr[], int low, int high) {
    if (high - low + 1 <= 10) {
        // Use Insertion Sort for small subarrays
        insertionSort(arr + low, high - low + 1);
    } else {
        // Use Quick Sort for large subarrays
        int pi = partition(arr, low, high);
        hybridSort(arr, low, pi - 1);  // Recursively sort left subarray
        hybridSort(arr, pi + 1, high); // Recursively sort right subarray
    }
}

// Function to generate random array
void generateRandomArray(int arr[], int n, int min = 1, int max = 10000) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + rand() % (max - min + 1);
    }
}

// Function to measure the execution time of the sorting algorithm
long long measureSortTime(void (*sortFunc)(int[], int, int), int arr[], int low, int high, const string& sortName) {
    auto start = high_resolution_clock::now();
    sortFunc(arr, low, high);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << sortName << " time for " << high - low + 1 << " elements: " << duration << " microseconds" << endl;
    return duration;
}

int main() {
    srand(time(0)); // Seed for random number generation

    // Array sizes to test
    int sizes[] = {10, 50, 100, 500, 1000};  // Sizes of arrays for testing
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    // Compare the performance of Hybrid Sort with Quick Sort
    for (int i = 0; i < numSizes; i++) {
        int n = sizes[i];

        // Generate random arrays
        int* arr = new int[n];
        generateRandomArray(arr, n); // Generate random array

        int* arrCopy = new int[n]; // Copy array for each sort
        copy(arr, arr + n, arrCopy);

        cout << "\nTesting Hybrid Sort for " << n << " elements:" << endl;
        long long hybridTime = measureSortTime(hybridSort, arrCopy, 0, n - 1, "Hybrid Sort");

        // Reset the array and measure time for Quick Sort
        copy(arr, arr + n, arrCopy);
        cout << "\nTesting Quick Sort for " << n << " elements:" << endl;

        long long quickTime = measureSortTime(quickSort, arrCopy, 0, n - 1, "Quick Sort");

        delete[] arr;
        delete[] arrCopy;
    }

    return 0;
}
