// 22520468
// Nguyen Huy Hoang
// Exercise 05

#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Node definition for Linked List, Queue, and Stack
template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(T val) : data(val), next(nullptr) {}
};

// Linked List implementation
template <typename T>
class LinkedList {
public:
    Node<T>* head;

    LinkedList() : head(nullptr) {}

    // Append a new node to the list
    void append(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = newNode;
            return;
        }
        Node<T>* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Binary Search to find the insertion position
    Node<T>* binarySearch(Node<T>* start, T value) {
        Node<T>* end = nullptr;
        while (start != end) {
            Node<T>* mid = start;
            Node<T>* fast = start;

            // Move `mid` to the middle and `fast` to the end of the list
            while (fast != end && fast->next != end) {
                fast = fast->next->next;
                mid = mid->next;
            }

            // If `mid`'s data is greater, move the end pointer
            if (mid->data > value) {
                end = mid;
            } else {
                start = mid->next;
            }
        }
        return start;
    }

    // Insertion Sort with Binary Search for finding insertion position
    void insertionSort() {
        if (!head || !head->next) return;

        Node<T>* sorted = nullptr;
        Node<T>* curr = head;
        while (curr) {
            Node<T>* next = curr->next;
            Node<T>* position = binarySearch(sorted, curr->data);

            if (!sorted || position == sorted) {
                curr->next = sorted;
                sorted = curr;
            } else {
                Node<T>* temp = sorted;
                while (temp->next != position) {
                    temp = temp->next;
                }
                temp->next = curr;
                curr->next = position;
            }
            curr = next;
        }
        head = sorted;
    }

    // Print the linked list
    void print() {
        Node<T>* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// Function to measure and print execution time
template <typename T>
long long measureSortTime(void (T::*sortFunc)(), T& container, const string& sortName) {
    auto start = high_resolution_clock::now();
    (container.*sortFunc)();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << sortName << " time: " << duration << " microseconds" << endl;
    return duration;
}

int main() {
    srand(time(0)); // Seed for random number generation

    int n = 100; // Test with 100 elements

    // Test Linked List with Binary Search Insertion Sort
    LinkedList<int> linkedList;
    for (int i = 0; i < n; ++i) {
        linkedList.append(rand() % 10000);
    }
    cout << "Sorting Linked List with Binary Search Insertion Sort:" << endl;
    measureSortTime(&LinkedList<int>::insertionSort, linkedList, "Binary Search Insertion Sort");

    return 0;
}
