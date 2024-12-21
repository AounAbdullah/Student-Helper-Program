#include <iostream>
#include "TM_Task.cpp" // Include Task class
using namespace std;

class GraphNode
{
public:
    Task task;
    int dependencies[10]; // Array for dependencies
    int dependencyCount;

    GraphNode() : dependencyCount(0)
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
    GraphNode GraphNodes[100]; // Fixed-size array for GraphNodes
    int GraphNodeCount;

    int findTaskIndex(const string &taskName)
    {
        for (int i = 0; i < GraphNodeCount; ++i)
        {
            if (GraphNodes[i].task.getname() == taskName)
            {
                return i;
            }
        }
        return -1; // Task not found
    }

public:
    Graph() : GraphNodeCount(0) {}

    // Add a new task
    void addTask(const Task &task)
    {
        if (findTaskIndex(task.getname()) != -1)
        {
            cout << "Task already exists!\n";
            return;
        }
        if (GraphNodeCount >= 100)
        {
            cout << "Maximum number of tasks reached!\n";
            return;
        }
        GraphNodes[GraphNodeCount].task = task;
        GraphNodeCount++;
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

        if (GraphNodes[taskIndex].dependencyCount < 10)
        {
            GraphNodes[taskIndex].dependencies[GraphNodes[taskIndex].dependencyCount++] = dependsOnIndex;
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
        for (int i = 0; i < GraphNodeCount; ++i)
        {
            cout << "Task: " << GraphNodes[i].task.getname() << " depends on: ";
            if (GraphNodes[i].dependencyCount == 0)
            {
                cout << "null";
            }
            else
            {
                for (int j = 0; j < GraphNodes[i].dependencyCount; ++j)
                {
                    cout << GraphNodes[GraphNodes[i].dependencies[j]].task.getname() << " ";
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
        for (int i = 0; i < GraphNodeCount; ++i)
        {
            for (int j = 0; j < GraphNodes[i].dependencyCount; ++j)
            {
                inDegree[GraphNodes[i].dependencies[j]]++;
            }
        }

        // Array for tasks with no dependencies
        int zeroInDegree[100];
        int zeroCount = 0;

        for (int i = 0; i < GraphNodeCount; ++i)
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
            executionOrder[execCount++] = GraphNodes[current].task.getname();

            for (int j = 0; j < GraphNodes[current].dependencyCount; ++j)
            {
                int dep = GraphNodes[current].dependencies[j];
                inDegree[dep]--;
                if (inDegree[dep] == 0)
                {
                    zeroInDegree[zeroCount++] = dep;
                }
            }
        }

        // Check for cycles
        if (execCount != GraphNodeCount)
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

// int main()
// {
//     Graph graph;

//     // Add tasks
//     graph.addTask(Task("Study", 2, "2024-12-20", false));
//     graph.addTask(Task("Submit", 1, "2024-12-18", false));
//     graph.addTask(Task("Meeting", 3, "2024-12-22", false));

//     // Add dependencies
//     graph.addDependency("Submit", "Study");
//     graph.addDependency("Meeting", "Submit");

//     // Display dependencies
//     graph.displayDependencies();

//     // Get execution order
//     graph.getExecutionOrder();

//     return 0;
// }
