#include <iostream> // For input/output
#include <thread>   // For std::this_thread::sleep_for
#include <chrono>   // For std::chrono::seconds
using namespace std;
// 2023049
// Abdullah Yasin

string PriorityNames[5]; // Array declared for quick access of Priority Names
int PriorityRank[5];     // Array declared for accessing Priority Ranks

struct Node
{
    int priorityrank_stack;
    Node *next;
};

class Stack
{
public:
    Node *top = NULL;

    // Function to push an element to the history stack
    void push(int val)
    {
        Node *newnode = new Node;
        newnode->priorityrank_stack = val;
        newnode->next = top;
        top = newnode;
    }

    // Function to pop an element from the history stack
    int pop()
    {
        if (top == NULL)
        {
            cout << "Stack Underflow" << endl;
            return -1; // Assuming -1 for error handling
        }
        else
        {
            int temp = top->priorityrank_stack;
            top = top->next;
            return temp;
        }
    }

    // Function to display the history stack elements
    void display()
    {
        Node *ptr;
        if (top == NULL)
        {
            cout << "History is empty" << endl;
        }
        else
        {
            ptr = top;
            cout << "History of accessed nodes (in terms of Priority Rank): ";
            while (ptr != NULL)
            {
                cout << ptr->priorityrank_stack << ", ";
                ptr = ptr->next;
            }
        }
        cout << endl;
    }
};

// Priority Class which stores detail of each Priority
class Priority
{
public:
    // Members storing each detail of Priority
    string priorityname;
    int priorityrank, subdivision, division, divisionbudget, subdivisionbudget;
    float prioritybudget;

    // Default constrcutor to initialize all members of class
    Priority()
    {
        priorityrank = 0;
        division = 0;
        subdivision = 0;
        divisionbudget = 0;
        subdivisionbudget = 0;
    }

    // Func which calculates division budget of each Priority
    int Calcdivbudget(int prbudget, int d)
    {
        if (d == 0) // indicating no division of budget
        {
            divisionbudget = 0;
        }

        else if (d == 1) // indicating daily division of budget
        {
            divisionbudget = prbudget / 30;
        }

        else if (d == 2) // indicating weekly division of budget
        {
            divisionbudget = prbudget / 4;
        }

        return divisionbudget;
    }

    // Func which calculates subdivision budget of each Priority
    int Calcsubdivbudget(int d_budget, int s_div)
    {
        if (s_div == 0)
        {
            return 0;
        }
        subdivisionbudget = d_budget / s_div;
        return subdivisionbudget;
    }

    // Function to set all members of the Priority Class
    void SetValues_Preset(string name, int div, int subdiv, int prrank, int totalbudget)
    {
        priorityname = name;
        division = div;
        subdivision = subdiv;
        priorityrank = prrank;

        if (priorityrank == 1)
            prioritybudget = totalbudget * 0.4;

        else if (priorityrank == 2)
            prioritybudget = totalbudget * 0.25;

        else if (priorityrank == 3)
            prioritybudget = totalbudget * 0.15;

        else if (priorityrank == 4)
            prioritybudget = totalbudget * 0.10;

        else if (priorityrank == 5)
            prioritybudget = totalbudget * 0.10;

        divisionbudget = Calcdivbudget(prioritybudget, division);
        subdivisionbudget = Calcsubdivbudget(divisionbudget, subdivision);
        PriorityNames[priorityrank - 1] = priorityname;
        PriorityRank[priorityrank] = priorityrank;
    }

    void SetValues_Custom(string name, int div, int subdiv, int prrank, int totalbudget, int prrank_allocation)
    {
        priorityname = name;
        division = div;
        subdivision = subdiv;
        priorityrank = prrank;

        prioritybudget = totalbudget * (static_cast<double>(prrank_allocation) / 100);
        divisionbudget = Calcdivbudget(prioritybudget, division);
        subdivisionbudget = Calcsubdivbudget(divisionbudget, subdivision);
        PriorityNames[priorityrank - 1] = priorityname;
        PriorityRank[priorityrank] = priorityrank;
    }
};

// Struct of Priority Node
struct PriorityNode
{
    Priority pr;
    PriorityNode *next;
    PriorityNode *prev;
};

// Class Budget Manager which acts as Double Linked List (DLL)
class BudgetManager
{
public:
    PriorityNode *head;
    PriorityNode *tail;
    Stack History;

    // Constructor to intialize head & tail pointers
    BudgetManager()
    {
        head = NULL;
        tail = NULL;
    }

    // Func to Insert new Priority Node in DLL
    void InsertNode(string name, int div, int subdiv, int prrank, int totalbudget, int budgetopt, int prrank_allocation)
    {
        PriorityNode *newNode = new PriorityNode; // Create new node

        if (budgetopt == 1)
        {
            newNode->pr.SetValues_Preset(name, div, subdiv, prrank, totalbudget);
        }

        else if (budgetopt == 2)
        {
            newNode->pr.SetValues_Custom(name, div, subdiv, prrank, totalbudget, prrank_allocation);
        }
        newNode->next = head; // New node points to the old head
        newNode->prev = NULL; // New node's previous is null

        if (head != NULL)
        {
            head->prev = newNode; // Update old head's previous pointer
        }
        else
        {
            tail = newNode; // If list was empty, newNode is also the tail
        }

        head = newNode;

        History.push(prrank);
    }

    // Func to Display all finalised Budget using recursion
    void DisplayAllBudget(PriorityNode *node)
    {
        if (node == NULL)
            return;

        cout << "For " << node->pr.priorityname << ":" << endl;
        cout << "The monthly budget is: " << node->pr.prioritybudget << endl;

        if (node->pr.divisionbudget != 0)
        {
            cout << "The budget of each division is: " << node->pr.divisionbudget << endl;
        }

        if (node->pr.subdivisionbudget != 0)
        {
            cout << "The budget of each subdivision is: " << node->pr.subdivisionbudget << endl;
        }

        History.push(node->pr.priorityrank);
        DisplayAllBudget(node->next);
    }

    // Func to Search & Display specific priority budget
    void SearchDisplaybudget(string searchName)
    {
        bool found = false;

        // Code for checking if the given Searchname exists or not
        // Hence reducing worst case time complexity of func
        for (int i = 0; i < 5; i++)
        {
            if (searchName == PriorityNames[i])
            {
                found = true;
                break;
            }
        }
        if (found == false)
            return;

        PriorityNode *current = head; // Start from the head of the linked list

        while (current != NULL)
        {
            if (current->pr.priorityname == searchName)
            {
                cout << "Priority Name: " << current->pr.priorityname << endl;
                cout << "Priority Rank: " << current->pr.priorityrank << endl;
                cout << "Monthly Budget: " << current->pr.prioritybudget << endl;

                if (current->pr.divisionbudget != 0)
                {
                    cout << "Division Budget (" << (current->pr.division == 1 ? "Daily" : "Weekly") << "): " << current->pr.divisionbudget << endl;
                }

                if (current->pr.subdivisionbudget != 0)
                {
                    cout << "Subdivision Budget: " << current->pr.subdivisionbudget << endl;
                }

                History.push(current->pr.priorityrank);
                break; // Exit loop after finding the priority
            }

            current = current->next;
        }
    }
};

int main()
{
    BudgetManager B;
    int budget_opt;

    // main User InterFace
    cout << "Welcome to Budget Manager!" << endl;

    do
    {

    } while (budget_opt != 10);
}