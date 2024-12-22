#include <iostream>
#include "TM_Task.cpp"        // Include Task class definition
#include "Graph.cpp"          // Include Graph for task dependencies
#include "Linked_List.cpp"    // Include Linked List for task storage
#include "Prioirty_Queue.cpp" // Include Priority Queue for task management

using namespace std;

void displayMenu() {
    cout << "\n===== Task Manager Menu =====\n";
    cout << "1. Add a Task\n";
    cout << "2. Add a Dependency\n";
    cout << "3. View Tasks\n";
    cout << "4. View Execution Order\n";
    cout << "5. Add Task to Priority Queue\n";
    cout << "6. Process Next Task\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Graph taskGraph;
    LinkedList taskList;
    PriorityQueue taskQueue(100); // Priority queue with capacity 100

    while (true) {
        displayMenu();

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, deadline;
                int priority;
                bool completed;

                cout << "Enter task name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter task priority (lower number = higher priority): ";
                cin >> priority;
                cout << "Enter deadline (YYYY-MM-DD): ";
                cin >> deadline;
                completed = false;

                Task newTask(name, priority, deadline, completed);

                // Add to graph and linked list
                taskGraph.addTask(newTask);
                taskList.append(newTask);

                cout << "Task added successfully.\n";
                break;
            }
            case 2: {
                string taskName, dependency;
                cout << "Enter the task name: ";
                cin.ignore();
                getline(cin, taskName);
                cout << "Enter the dependency task name: ";
                getline(cin, dependency);

                taskGraph.addDependency(taskName, dependency);
                cout << "Dependency added successfully.\n";
                break;
            }
            case 3: {
                cout << "\nAll Tasks:\n";
                taskList.print();
                cout << "\nTask Dependencies:\n";
                taskGraph.displayDependencies();
                break;
            }
            case 4: {
                cout << "\nExecution Order:\n";
                taskGraph.getExecutionOrder();
                break;
            }
            case 5: {
                string name;
                cout << "Enter the task name to add to the priority queue: ";
                cin.ignore();
                getline(cin, name);

                Node* taskNode = taskList.head;
                while (taskNode != nullptr) {
                    if (taskNode->value.getname() == name) {
                        taskQueue.enqueue(taskNode->value);
                        cout << "Task added to the priority queue.\n";
                        break;
                    }
                    taskNode = taskNode->next;
                }
                if (taskNode == nullptr) {
                    cout << "Task not found in the list.\n";
                }
                break;
            }
            case 6: {
                if (!taskQueue.isEmpty()) {
                    Task nextTask = taskQueue.dequeue();
                    cout << "\nProcessing Task:\n";
                    cout << "Task Name: " << nextTask.getname() << "\n";
                    cout << "Priority: " << nextTask.getPriority() << "\n";
                    cout << "Deadline: " << nextTask.getDeadline() << "\n";
                    taskList.removeByName(nextTask.getname());
                } else {
                    cout << "No tasks in the priority queue.\n";
                }
                break;
            }
            case 7: {
                cout << "Exiting Task Manager. Goodbye!\n";
                return 0;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
