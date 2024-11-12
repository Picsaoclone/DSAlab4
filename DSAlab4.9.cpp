// 22520468
// Nguyen Huy Hoang
// Exercise 09

#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Define a Point structure for 2D points
struct Point {
    int x, y;

    // Constructor to initialize the point
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    // Calculate the squared distance from the origin (0, 0)
    int squaredDistance() const {
        return x * x + y * y;
    }
};

// Insertion Sort for points based on squared distance
void insertionSort(Point arr[], int n) {
    for (int i = 1; i < n; i++) {
        Point key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].squaredDistance() > key.squaredDistance()) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Partition function for Quick Sort
int partition(Point arr[], int low, int high) {
    Point pivot = arr[high];  // pivot element
    int i = low - 1;  // index of smaller element
    for (int j = low; j < high; j++) {
        if (arr[j].squaredDistance() <= pivot.squaredDistance()) {
            i++;
            // Swap arr[i] and arr[j]
            Point temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Swap arr[i + 1] and arr[high]
    Point temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Quick Sort function
void quickSort(Point arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);  // Recursively sort left subarray
        quickSort(arr, pi + 1, high); // Recursively sort right subarray
    }
}

// Merge Sort helper functions
void merge(Point arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Point* L = new Point[n1];
    Point* R = new Point[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].squaredDistance() <= R[j].squaredDistance()) {
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

void mergeSort(Point arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Function to generate random points in a 2D space
void generateRandomPoints(Point arr[], int n, int min = 0, int max = 100) {
    for (int i = 0; i < n; i++) {
        arr[i] = Point(min + rand() % (max - min + 1), min + rand() % (max - min + 1));
    }
}

// Function to measure the execution time for sorting algorithms requiring only size
long long measureSortTime(void (*sortFunc)(Point[], int), Point arr[], int n, const string& sortName) {
    auto start = high_resolution_clock::now();
    sortFunc(arr, n);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << sortName << " time for " << n << " points: " << duration << " microseconds" << endl;
    return duration;
}

// Function to measure the execution time for sorting algorithms requiring low/high indices
long long measureSortTime(void (*sortFunc)(Point[], int, int), Point arr[], int low, int high, const string& sortName) {
    auto start = high_resolution_clock::now();
    sortFunc(arr, low, high);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << sortName << " time for " << high - low + 1 << " points: " << duration << " microseconds" << endl;
    return duration;
}

int main() {
    srand(time(0)); // Seed for random number generation

    // Array sizes to test
    int sizes[] = {10, 50, 100, 500, 1000};  // Sizes of arrays for testing
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    // Compare the performance of Insertion Sort, Quick Sort, and Merge Sort on points
    for (int i = 0; i < numSizes; i++) {
        int n = sizes[i];

        // Generate random points in 2D space
        Point* arr = new Point[n];
        generateRandomPoints(arr, n);

        Point* arrCopy = new Point[n]; // Copy array for each sort
        copy(arr, arr + n, arrCopy);

        cout << "\nTesting Insertion Sort for " << n << " points:" << endl;
        long long insertionTime = measureSortTime(insertionSort, arrCopy, n, "Insertion Sort");

        // Reset the array and measure time for Quick Sort
        copy(arr, arr + n, arrCopy);
        cout << "\nTesting Quick Sort for " << n << " points:" << endl;
        long long quickTime = measureSortTime(quickSort, arrCopy, 0, n - 1, "Quick Sort");

        // Reset the array and measure time for Merge Sort
        copy(arr, arr + n, arrCopy);
        cout << "\nTesting Merge Sort for " << n << " points:" << endl;
        long long mergeTime = measureSortTime(mergeSort, arrCopy, 0, n - 1, "Merge Sort");

        delete[] arr;
        delete[] arrCopy;
    }

    return 0;
}
