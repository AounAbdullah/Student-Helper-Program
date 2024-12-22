#include "TM_Task.cpp"
#include "Graph.cpp"

#include "scheduler.cpp"

using namespace std;

void displayMenu()
{
    cout << "\n===== Task Manager Menu =====\n";
    cout << "1. Add a Task\n";
    cout << "2. Add a Dependency\n";
    cout << "3. View Active Tasks\n";
    cout << "4. View Completed Tasks\n";
    cout << "5. Execute Next Task\n";
    cout << "6. Defer a Task\n";
    cout << "7. View Execution Order\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}

int menu()
{
    Scheduler scheduler(100); // Scheduler with priority queue capacity 100
    Graph taskGraph;

    while (true)
    {
        displayMenu();

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string name, deadline;
            int priority;

            cout << "Enter task name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter priority (lower = higher priority): ";
            cin >> priority;
            cout << "Enter deadline (YYYY-MM-DD): ";
            cin >> deadline;

            Task newTask(name, priority, deadline, false);

            // Add task to Scheduler and Graph
            scheduler.addTask(newTask);
            taskGraph.addTask(newTask);

            cout << "Task added successfully.\n";
            break;
        }
        case 2:
        {
            string taskName, dependency;
            cout << "Enter task name: ";
            cin.ignore();
            getline(cin, taskName);
            cout << "Enter dependency task name: ";
            getline(cin, dependency);

            taskGraph.addDependency(taskName, dependency);
            cout << "Dependency added successfully.\n";
            break;
        }
        case 3:
        {
            cout << "Active Tasks:\n";
            scheduler.displayAllTasks();
            break;
        }
        case 4:
        {
            cout << "Completed Tasks:\n";
            scheduler.displayCompletedTasks();
            break;
        }
        case 5:
        {
            scheduler.executeNextTask();
            break;
        }
        case 6:
        {
            string taskName;
            cout << "Enter task name to defer: ";
            cin.ignore();
            getline(cin, taskName);

            scheduler.deferTask(taskName);
            break;
        }
        case 7:
        {
            taskGraph.getExecutionOrder();
            break;
        }
        case 8:
        {
            cout << "Exiting Task Manager. Goodbye!\n";
            return 0;
        }
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
