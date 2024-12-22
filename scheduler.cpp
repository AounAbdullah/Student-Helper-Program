#include <iostream>
#include <string>
#include <queue>
#include <list>
#include "TM_Task.cpp"
#include "Prioirty_Queue.cpp"
#include "Linked_List.cpp"


class Scheduler {
private:
    PriorityQueue taskQueue;              // Priority queue for active tasks
    LinkedList completedTasks;            // Linked list for completed tasks
    LinkedList pendingTasks;              // Linked list for deferred tasks
    int totalTasks = 0;                   // Counter for total tasks
    int completedCount = 0;               // Counter for completed tasks

public:
    // Constructor
    Scheduler(int capacity) : taskQueue(capacity) {}

    // Add a task to the priority queue
    void addTask(const Task& task) {
        taskQueue.enqueue(task);
        totalTasks++;
    }
    
    // Remove a task by name
    void removeTask(const std::string& taskName) {
        if (!taskQueue.removeByName(taskName)) {
            std::cout << "Task not found in the priority queue.\n";
        }
    }

    // Defer a task (move to pending list)
    void deferTask(const std::string& taskName) {
        Task deferredTask;
        if (taskQueue.removeByName(taskName)) {
            deferredTask = taskQueue.peek(); // Assuming taskQueue.peek() fetches the removed task
            pendingTasks.append(deferredTask);
        } else {
            std::cout << "Task not found to defer.\n";
        }
    }

    // Execute the next task (highest priority)
    void executeNextTask() {
        if (!taskQueue.isEmpty()) {
            Task nextTask = taskQueue.dequeue();
            nextTask.setCompletionStatus(true); // Assuming Task has a `markComplete()` method
            completedTasks.append(nextTask);
            completedCount++;
        } else {
            std::cout << "No tasks to execute.\n";
        }
    }

    // Display all tasks
    void displayAllTasks() {
        std::cout << "Active Tasks:\n";
        taskQueue.display();
        std::cout << "Pending Tasks:\n";
        pendingTasks.print();
    }

    // Display completed tasks
    void displayCompletedTasks() {
        std::cout << "Completed Tasks:\n";
        completedTasks.print();
    }

    // Summary functions
    int getTotalTasks() { return totalTasks; }
    int getCompletedTaskCount()  { return completedCount; }
    int getPendingTaskCount()  { return pendingTasks.size(); }
};

int main() {
    Scheduler dailyScheduler(10); // Create a scheduler with capacity 10

    // Create some tasks
    Task task1("Study for exam", 2, "2024-12-20", false);
    Task task2("Submit project", 1, "2024-12-18", false);
    Task task3("Attend meeting", 3, "2024-12-22", false);

    // Add tasks
    dailyScheduler.addTask(task1);
    dailyScheduler.addTask(task2);
    dailyScheduler.addTask(task3);

    // Display all tasks
    dailyScheduler.displayAllTasks();

    // Execute next task
    dailyScheduler.executeNextTask();

    // Display completed tasks
    dailyScheduler.displayCompletedTasks();

    // Defer a task
    dailyScheduler.deferTask("Attend meeting");
    dailyScheduler.displayAllTasks();

    return 0;
}

