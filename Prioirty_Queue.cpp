#include <iostream>
#include <string>
#include <stdexcept>
#include "TM_Task.cpp"
using namespace std;

// Priority Queue for Task Management using Custom Task Class
class PriorityQueue {
private:
    Task* heap; // Dynamically allocated array for heap
    int capacity;
    int size; 

    // Helper function to maintain heap property (min-heap)
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index].getPriority() < heap[parent].getPriority()) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // Helper function to maintain heap property (min-heap)
    void heapifyDown(int index) {
        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int smallest = index;

            if (leftChild < size && heap[leftChild].getPriority() < heap[smallest].getPriority()) {
                smallest = leftChild;
            }
            if (rightChild < size && heap[rightChild].getPriority() < heap[smallest].getPriority()) {
                smallest = rightChild;
            }

            if (smallest != index) {
                swap(heap[index], heap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }

public:
    // Constructor
    PriorityQueue(int cap) : capacity(cap), size(0) {
        heap = new Task[capacity];
    }

    // Destructor
    ~PriorityQueue() {
        delete[] heap;
    }

    // Add a task to the priority queue
    void enqueue(const Task& task) {
        if (size == capacity) {
            throw overflow_error("Priority queue is full!");
        }

        heap[size] = task;
        heapifyUp(size);
        size++;
    }

    // Remove and return the highest-priority task
    Task dequeue() {
        if (size == 0) {
            throw runtime_error("Priority queue is empty!");
        }

        Task topTask = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return topTask;
    }

    // Peek at the highest-priority task without removing it
    Task peek() const {
        if (size == 0) {
            throw runtime_error("Priority queue is empty!");
        }
        return heap[0];
    }

    // Check if the priority queue is empty
    bool isEmpty() const {
        return size == 0;
    }

    // Display all tasks in the priority queue (for debugging purposes)
    void display() const {
        cout << "Priority Queue Contents:\n";
        for (int i = 0; i < size; ++i) {
            cout << "Task: " << heap[i].getname() << ", Priority: " << heap[i].getPriority()
                 << ", Deadline: " << heap[i].getDeadline() << "\n";
        }
    }
};

// Example usage
int main() {
    PriorityQueue pq(10); // Create a priority queue with capacity 10

    pq.enqueue(Task("Study for exam", 2, "2024-12-20", false));
    pq.enqueue(Task("Submit project", 1, "2024-12-18", false));
    pq.enqueue(Task("Attend meeting", 3, "2024-12-22", false));

    pq.display();

    cout << "\nDequeuing tasks by priority:\n";
    while (!pq.isEmpty()) {
        Task t = pq.dequeue();
        cout << "Task: " << t.getname() << ", Priority: " << t.getPriority()
             << ", Deadline: " << t.getDeadline() << "\n";
    }

    return 0;
}
