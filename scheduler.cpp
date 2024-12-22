#include <iostream>
#include <string>
#include "TM_Task.cpp"
#include "Priority_Queue.cpp"
#include "Linked_List.cpp"

using namespace std;

class Scheduler
{
private:
    PriorityQueue taskQueue;   // Priority queue for active tasks
    LinkedList completedTasks; // Linked list for completed tasks
    LinkedList pendingTasks;   // Linked list for deferred tasks
    int totalTasks = 0;        // Counter for total tasks
    int completedCount = 0;    // Counter for completed tasks

public:
    // Constructor
    Scheduler(int capacity) : taskQueue(capacity) {}

    // Add a task to the priority queue
    void addTask(const Task &task)
    {
        taskQueue.enqueue(task);
        totalTasks++;
    }

    // Remove a task by name
    void removeTask(const string &taskName)
    {
        if (!taskQueue.removeByName(taskName))
        {
            cout << "Task not found in the priority queue.\n";
        }
    }

    // Defer a task (move to pending list)
    void deferTask(const string &taskName)
    {
        Task deferredTask;
        bool found = false;

        // Temporary storage for tasks during removal
        PriorityQueue tempQueue(taskQueue.capacity);

        // Find the task in the priority queue
        while (!taskQueue.isEmpty())
        {
            Task currentTask = taskQueue.dequeue();
            if (currentTask.getname() == taskName)
            {
                deferredTask = currentTask;
                found = true;
            }
            else
            {
                tempQueue.enqueue(currentTask);
            }
        }

        // Restore remaining tasks to the original priority queue
        while (!tempQueue.isEmpty())
        {
            taskQueue.enqueue(tempQueue.dequeue());
        }

        if (found)
        {
            // Defer the task by adding it to the pending list
            pendingTasks.append(deferredTask);
            cout << "Task '" << taskName << "' deferred successfully.\n";
        }
        else
        {
            cout << "Task '" << taskName << "' not found in the priority queue.\n";
        }
    }
    void reactivateTask(const string &taskName)
    {
        Node *temp = pendingTasks.head;
        while (temp)
        {
            if (temp->value.getname() == taskName)
            {
                // Move task back to active tasks
                taskQueue.enqueue(temp->value);

                // Remove task from pending list
                pendingTasks.removeByName(taskName);

                cout << "Task '" << taskName << "' reactivated successfully.\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Task '" << taskName << "' not found in pending tasks.\n";
    }

    // Execute the next task (highest priority)
    void executeNextTask()
    {
        if (!taskQueue.isEmpty())
        {
            Task nextTask = taskQueue.dequeue();
            nextTask.setCompletionStatus(true);
            completedTasks.append(nextTask);
            completedCount++;
        }
        else
        {
            cout << "No tasks to execute.\n";
        }
    }

    // Display all tasks
    void displayAllTasks()
    {
        cout << "===== Active Tasks =====\n";
        if (taskQueue.isEmpty())
        {
            cout << "No active tasks.\n";
        }
        else
        {
            taskQueue.display();
        }

        cout << "\n===== Pending Tasks =====\n";
        if (pendingTasks.size() == 0)
        {
            cout << "No pending tasks.\n";
        }
        else
        {
            pendingTasks.print();
        }
    }

    // Display completed tasks
    void displayCompletedTasks()
    {
        cout << "Completed Tasks:\n";
        completedTasks.print();
    }

    // Summary functions
    int getTotalTasks() { return totalTasks; }
    int getCompletedTaskCount() { return completedCount; }
    int getPendingTaskCount() { return pendingTasks.size(); }
};
