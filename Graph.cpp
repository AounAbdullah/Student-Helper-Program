#include <iostream>
#include "TM_Task.cpp" // Include Task class
using namespace std;

class Node
{
public:
    Task task;
    int dependencies[10]; // Array for dependencies
    int dependencyCount;

    Node() : dependencyCount(0)
    {
        for (int i = 0; i < 10; ++i)
        {
            dependencies[i] = -1;
        }
    }
};

class Graph
{
private:
    Node nodes[100]; // Fixed-size array for nodes
    int nodeCount;

    int findTaskIndex(const string &taskName)
    {
        for (int i = 0; i < nodeCount; ++i)
        {
            if (nodes[i].task.getname() == taskName)
            {
                return i;
            }
        }
        return -1; // Task not found
    }

public:
    Graph() : nodeCount(0) {}

    // Add a new task
    void addTask(const Task &task)
    {
        if (findTaskIndex(task.getname()) != -1)
        {
            cout << "Task already exists!\n";
            return;
        }
        if (nodeCount >= 100)
        {
            cout << "Maximum number of tasks reached!\n";
            return;
        }
        nodes[nodeCount].task = task;
        nodeCount++;
    }

    // Add a dependency between tasks
    void addDependency(const string &taskName, const string &dependsOn)
    {
        int taskIndex = findTaskIndex(taskName);
        int dependsOnIndex = findTaskIndex(dependsOn);

        if (taskIndex == -1 || dependsOnIndex == -1)
        {
            cout << "One or both tasks not found!\n";
            return;
        }

        if (nodes[taskIndex].dependencyCount < 10)
        {
            nodes[taskIndex].dependencies[nodes[taskIndex].dependencyCount++] = dependsOnIndex;
        }
        else
        {
            cout << "Maximum dependencies reached for task: " << taskName << "\n";
        }
    }

    // Display all tasks and their dependencies
    void displayDependencies() const
    {
        cout << "Task Dependencies:\n";
        for (int i = 0; i < nodeCount; ++i)
        {
            cout << "Task: " << nodes[i].task.getname() << " depends on: ";
            if (nodes[i].dependencyCount == 0)
            {
                cout << "null";
            }
            else
            {
                for (int j = 0; j < nodes[i].dependencyCount; ++j)
                {
                    cout << nodes[nodes[i].dependencies[j]].task.getname() << " ";
                }
            }
            cout << endl;
        }
    }

    // Topological Sort to get execution order
    void getExecutionOrder()
    {
        int inDegree[100] = {0};

        // Calculate in-degrees
        for (int i = 0; i < nodeCount; ++i)
        {
            for (int j = 0; j < nodes[i].dependencyCount; ++j)
            {
                inDegree[nodes[i].dependencies[j]]++;
            }
        }

        // Array for tasks with no dependencies
        int zeroInDegree[100];
        int zeroCount = 0;

        for (int i = 0; i < nodeCount; ++i)
        {
            if (inDegree[i] == 0)
            {
                zeroInDegree[zeroCount++] = i;
            }
        }

        // Process tasks in topological order
        string executionOrder[100];
        int execCount = 0;

        while (zeroCount > 0)
        {
            int current = zeroInDegree[--zeroCount];
            executionOrder[execCount++] = nodes[current].task.getname();

            for (int j = 0; j < nodes[current].dependencyCount; ++j)
            {
                int dep = nodes[current].dependencies[j];
                inDegree[dep]--;
                if (inDegree[dep] == 0)
                {
                    zeroInDegree[zeroCount++] = dep;
                }
            }
        }

        // Check for cycles
        if (execCount != nodeCount)
        {
            cout << "Cyclic dependency detected!\n";
            return;
        }

        // Display execution order
        cout << "\nExecution Order:\n";
        for (int i = 0; i < execCount; ++i)
        {
            cout << executionOrder[i] << " ";
        }
        cout << "\n";
    }
};

int main()
{
    Graph graph;

    // Add tasks
    graph.addTask(Task("Study", 2, "2024-12-20", false));
    graph.addTask(Task("Submit", 1, "2024-12-18", false));
    graph.addTask(Task("Meeting", 3, "2024-12-22", false));

    // Add dependencies
    graph.addDependency("Submit", "Study");
    graph.addDependency("Meeting", "Submit");

    // Display dependencies
    graph.displayDependencies();

    // Get execution order
    graph.getExecutionOrder();

    return 0;
}
