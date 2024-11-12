#include <iostream>
#include <cstdlib>
#include <chrono>
#include <stdexcept>  // Add this line to include runtime_error
using namespace std;
using namespace std::chrono;

// Define the Node structure for Linked List, Queue, and Stack
template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node(T val) : data(val), next(nullptr) {}
};

// Linked List Implementation
template <typename T>
class LinkedList {
public:
    Node<T>* head;
    LinkedList() : head(nullptr) {}

    void append(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    void bubbleSort() {
        if (!head) return;
        bool swapped;
        do {
            swapped = false;
            Node<T>* curr = head;
            while (curr && curr->next) {
                if (curr->data > curr->next->data) {
                    swap(curr->data, curr->next->data);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);
    }

    void insertionSort() {
        if (!head || !head->next) return;

        Node<T>* sorted = nullptr;
        Node<T>* curr = head;
        while (curr) {
            Node<T>* next = curr->next;
            if (!sorted || sorted->data >= curr->data) {
                curr->next = sorted;
                sorted = curr;
            } else {
                Node<T>* temp = sorted;
                while (temp->next && temp->next->data < curr->data) {
                    temp = temp->next;
                }
                curr->next = temp->next;
                temp->next = curr;
            }
            curr = next;
        }
        head = sorted;
    }

    void selectionSort() {
        if (!head) return;

        for (Node<T>* i = head; i != nullptr; i = i->next) {
            Node<T>* minNode = i;
            for (Node<T>* j = i->next; j != nullptr; j = j->next) {
                if (j->data < minNode->data) minNode = j;
            }
            if (minNode != i) swap(i->data, minNode->data);
        }
    }

    void print() const {
        Node<T>* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// Queue Implementation (using Linked List)
template <typename T>
class Queue {
public:
    Node<T>* front;
    Node<T>* rear;

    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    T dequeue() {
        if (!front) throw runtime_error("Queue is empty");
        Node<T>* temp = front;
        T val = front->data;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        return val;
    }

    bool isEmpty() const { return front == nullptr; }

    void bubbleSort() {
        int count = 0;
        Node<T>* temp = front;
        while (temp) { count++; temp = temp->next; }

        T* arr = new T[count];
        temp = front;
        for (int i = 0; i < count; i++) arr[i] = dequeue();

        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
            }
        }
        for (int i = 0; i < count; i++) enqueue(arr[i]);
        delete[] arr;
    }

    void print() const {
        Node<T>* temp = front;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// Stack Implementation (using Linked List)
template <typename T>
class Stack {
public:
    Node<T>* top;

    Stack() : top(nullptr) {}

    void push(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = top;
        top = newNode;
    }

    T pop() {
        if (!top) throw runtime_error("Stack is empty");
        Node<T>* temp = top;
        T val = top->data;
        top = top->next;
        delete temp;
        return val;
    }

    bool isEmpty() const { return top == nullptr; }

    void bubbleSort() {
        int count = 0;
        Node<T>* temp = top;
        while (temp) { count++; temp = temp->next; }

        T* arr = new T[count];
        temp = top;
        for (int i = 0; i < count; i++) arr[i] = pop();

        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
            }
        }
        for (int i = count - 1; i >= 0; i--) push(arr[i]);
        delete[] arr;
    }

    void print() const {
        Node<T>* temp = top;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// Function to measure and print execution time
template <typename T>
void measureSortTime(void (T::*sortFunc)(), T& container, const string& containerName, const string& sortName) {
    auto start = high_resolution_clock::now();
    (container.*sortFunc)();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << containerName << " - " << sortName << " time: " << duration << " microseconds" << endl;
}

int main() {
    srand(time(0)); // Seed for random number generation
    const int n = 100; // Test with 100 elements

    // Test Linked List with all sorting algorithms
    LinkedList<int> linkedList1, linkedList2, linkedList3;
    for (int i = 0; i < n; ++i) {
        int value = rand() % 10000;
        linkedList1.append(value);
        linkedList2.append(value);
        linkedList3.append(value);
    }
    measureSortTime(&LinkedList<int>::bubbleSort, linkedList1, "LinkedList", "Bubble Sort");
    measureSortTime(&LinkedList<int>::insertionSort, linkedList2, "LinkedList", "Insertion Sort");
    measureSortTime(&LinkedList<int>::selectionSort, linkedList3, "LinkedList", "Selection Sort");

    // Test Queue with bubble sort
    Queue<int> queue1;
    for (int i = 0; i < n; ++i) queue1.enqueue(rand() % 10000);
    measureSortTime(&Queue<int>::bubbleSort, queue1, "Queue", "Bubble Sort");

    // Test Stack with bubble sort
    Stack<int> stack1;
    for (int i = 0; i < n; ++i) stack1.push(rand() % 10000);
    measureSortTime(&Stack<int>::bubbleSort, stack1, "Stack", "Bubble Sort");

    return 0;
}

