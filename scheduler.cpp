#include <iostream>
#include <string>
#include <queue>
#include <list>
#include "TM_Task.cpp"
#include "Prioirty_Queue.cpp"
#include "Linked_List.cpp"

class Scheduler {
private:
    PriorityQueue taskQueue;              // Priority Queue to hold tasks based on priority
    LinkedList completedTasks;            // Linked List for completed tasks
    LinkedList pendingTasks;              // Linked List for deferred tasks

    Task currentTask;                     // The task currently being executed
    std::string schedulerName;            // Scheduler instance name
    int totalTasks = 0;                   // Counter for total tasks
    int completedCount = 0;               // Counter for completed tasks

public:
    // Constructor
    Scheduler(const std::string& name) : schedulerName(name) {}

    // 1. Task Management Functions

    // Add a new task to the priority queue
    void addTask(const Task& task) {
        taskQueue.push(task);
        totalTasks++;
    }

    // Remove a task by name from the priority queue
    void removeTask(const std::string& taskName) {
        taskQueue.remove(taskName);
    }

    // 2. Scheduling Functions

    // Get the next task based on priority (highest priority task)
    Task getNextTask() {
        return taskQueue.top();
    }

    // Defer a task (move it to pendingTasks)
    void deferTask(const std::string& taskName) {
        Task deferredTask = taskQueue.removeAndGet(taskName);
        pendingTasks.add(deferredTask);
    }

    // Execute the next task (highest priority task)
    void executeNextTask() {
        if (!taskQueue.empty()) {
            currentTask = taskQueue.top();
            taskQueue.pop();
            completedTasks.add(currentTask);
            completedCount++;
        } else {
            std::cout << "No tasks left to execute." << std::endl;
        }
    }

    // 3. Status Queries

    // Display all tasks in the taskQueue and pendingTasks
    void displayAllTasks() {
        taskQueue.display();
        pendingTasks.display();
    }

    // Display completed tasks
    void displayCompletedTasks() {
        completedTasks.display();
    }

    // Display pending tasks
    void displayPendingTasks() {
        pendingTasks.display();
    }

    // 4. Summary Functions

    int getTotalTasks() const {
        return totalTasks;
    }

    int getCompletedTaskCount() const {
        return completedCount;
    }

    int getPendingTaskCount() const {
        return pendingTasks.size();
    }
};

int main() {
    Scheduler dailyScheduler("Daily Scheduler");

    // Create some tasks
    Task task1("Task 1", 2);
    Task task2("Task 2", 1);
    Task task3("Task 3", 3);

    // Add tasks to scheduler
    dailyScheduler.addTask(task1);
    dailyScheduler.addTask(task2);
    dailyScheduler.addTask(task3);

    // Display all tasks
    dailyScheduler.displayAllTasks();

    // Execute next task
    dailyScheduler.executeNextTask();

    // Display completed tasks
    dailyScheduler.displayCompletedTasks();

    // Display pending tasks
    dailyScheduler.displayPendingTasks();

    // Defer a task
    dailyScheduler.deferTask("Task 3");
    dailyScheduler.displayPendingTasks();

    return 0;
}
