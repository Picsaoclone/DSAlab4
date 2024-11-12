// 22520468
// Nguyen Huy Hoang
// Exercise 03

#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib>
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
void generateRandomIntArray(int arr[], int n, int min = 1, int max = 10000) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + rand() % (max - min + 1);
    }
}

// Function to generate random floating-point numbers in an array
void generateRandomFloatArray(float arr[], int n, float min = 1.0f, float max = 10000.0f) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
    }
}

// Function to generate random strings in an array
void generateRandomStringArray(string arr[], int n, int length = 10) {
    const string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (int i = 0; i < n; i++) {
        string str = "";
        for (int j = 0; j < length; j++) {
            str += characters[rand() % characters.size()];
        }
        arr[i] = str;
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

        // Test with integer arrays
        int* intArr = new int[n];
        generateRandomIntArray(intArr, n);

        int* intArrCopy = new int[n]; // Copy array for each sort
        cout << "\nSorting " << n << " integer elements:\n";
        copyArray(intArr, intArrCopy, n);
        long long bubbleTime = measureSortTime(bubbleSort, intArrCopy, n, "Bubble Sort");

        copyArray(intArr, intArrCopy, n);
        long long insertionTime = measureSortTime(insertionSort, intArrCopy, n, "Insertion Sort");

        copyArray(intArr, intArrCopy, n);
        long long selectionTime = measureSortTime(selectionSort, intArrCopy, n, "Selection Sort");

        delete[] intArr;
        delete[] intArrCopy;

        // Test with floating-point arrays
        float* floatArr = new float[n];
        generateRandomFloatArray(floatArr, n);

        float* floatArrCopy = new float[n]; // Copy array for each sort
        cout << "\nSorting " << n << " float elements:\n";
        copyArray(floatArr, floatArrCopy, n);
        bubbleTime = measureSortTime(bubbleSort, floatArrCopy, n, "Bubble Sort");

        copyArray(floatArr, floatArrCopy, n);
        insertionTime = measureSortTime(insertionSort, floatArrCopy, n, "Insertion Sort");

        copyArray(floatArr, floatArrCopy, n);
        selectionTime = measureSortTime(selectionSort, floatArrCopy, n, "Selection Sort");

        delete[] floatArr;
        delete[] floatArrCopy;

        // Test with string arrays
        string* stringArr = new string[n];
        generateRandomStringArray(stringArr, n);

        string* stringArrCopy = new string[n]; // Copy array for each sort
        cout << "\nSorting " << n << " string elements:\n";
        copyArray(stringArr, stringArrCopy, n);
        bubbleTime = measureSortTime(bubbleSort, stringArrCopy, n, "Bubble Sort");

        copyArray(stringArr, stringArrCopy, n);
        insertionTime = measureSortTime(insertionSort, stringArrCopy, n, "Insertion Sort");

        copyArray(stringArr, stringArrCopy, n);
        selectionTime = measureSortTime(selectionSort, stringArrCopy, n, "Selection Sort");

        delete[] stringArr;
        delete[] stringArrCopy;
    }

    return 0;
}
