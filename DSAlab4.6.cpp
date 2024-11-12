// 22520468
// Nguyen Huy Hoang
// Exercise 06

#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Function to heapify a subtree rooted at index `i`
// `n` is the size of the heap
void heapify(int arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // Left child index
    int right = 2 * i + 2; // Right child index

    // Check if left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Check if right child is larger than the largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If largest is not root, swap it with the largest child and continue heapifying
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Function to build a max heap
void buildMaxHeap(int arr[], int n) {
    // Start from the last non-leaf node and heapify each node
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// Function to find the maximum value using heap sort without fully sorting the array
int findMaxUsingHeapSort(int arr[], int n) {
    // Build a max heap
    buildMaxHeap(arr, n);

    // The root of the max heap contains the maximum element
    return arr[0];
}

int main() {
    srand(time(0)); // Seed for random number generation

    // Generate an array with random values
    int n = 100;
    int arr[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 10000; // Random numbers between 0 and 9999
    }

    // Find the maximum value using Heap Sort method
    cout << "Finding the maximum value using Heap Sort:" << endl;
    int maxValue = findMaxUsingHeapSort(arr, n);
    cout << "Maximum value: " << maxValue << endl;

    return 0;
}
