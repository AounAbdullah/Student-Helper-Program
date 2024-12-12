#include <iostream>  // For input/output
using namespace std;
//2023049
//Abdullah Yasin

//Priority Class which stores detail of each Priority
class Priority
{
    public:

    //members storing each detail of Priority
    string priorityname;
    int priorityrank, subdivision, division, prioritybudget, divisionbudget, subdivisionbudget;

    //default constrcutor to initialize all members of class
    Priority()
    {
        priorityrank = NULL;
        division = NULL;
        subdivision = NULL;
        prioritybudget = NULL;
        divisionbudget = NULL;
        subdivisionbudget = NULL;
    }

    //function to set all members of the Priority Class
    void SetValues(string name, int div, int subdiv, int prrank, int totalbudget)
    {
        priorityname = name;
        division = div;
        subdivision = subdiv;
        priorityrank = prrank;

        if (priorityrank == 1)
            prioritybudget = totalbudget * 0.4;

        else if (priorityrank == 2)
            prioritybudget  = totalbudget * 0.25;

        else if (priorityrank == 3)
            prioritybudget  = totalbudget * 0.15;

        else if (priorityrank == 4)
            prioritybudget  = totalbudget * 0.10;

        else if (priorityrank == 5)
            prioritybudget  = totalbudget * 0.10;
    }


    //func which calculates division budget of each Priority
    int Calcdivbudget()
    {
        if (division == 0) // indicating no division of budget
        {
            divisionbudget = 0;
        }

        else if (division == 1) // indicating daily division of budget
        {
            divisionbudget = prioritybudget/30;
        }

        else if (division == 2) // indicating weekly division of budget
        {
            divisionbudget = prioritybudget/4;
        }

        return divisionbudget;
    }

    //func which calculates subdivision budget of each Priority
    int Calcsubdivbudget()
    {
        
        return subdivisionbudget;
    }

};


//struct of Priority Node 
struct PriorityNode
{
    Priority pr;
    PriorityNode* next;
    PriorityNode* prev;
};


//Class Budget Manager which acts as Double Linked List (DLL)
class BudgetManager
{
    private:
    PriorityNode* head;
    PriorityNode* tail;

    public:

    //constructor to intialize head & tail pointers
    BudgetManager()
    {
        head = NULL;
        tail = NULL;
    }

    //func to Insert new Priority Node in DLL
    void InsertNode(string name, int div, int subdiv, int prrank, int totalbudget)
    {
        PriorityNode* newNode = new PriorityNode;    // Create new node
        newNode->pr.SetValues(name, div, subdiv, prrank, totalbudget);
        newNode->next = head;        // New node points to the old head
        newNode->prev = NULL;     // New node's previous is null

        if (head != NULL) 
        {
            head->prev = newNode;    // Update old head's previous pointer
        } 
        else 
        {
            tail = newNode;          // If list was empty, newNode is also the tail
        }

        head = newNode; 
    }

    //func to Display all finalised Budget
    void DisplayAllBudget()
    {
        PriorityNode* current = head;
        while (current != NULL) {
            cout << "For " << current->pr.priorityname << ":" << endl;
            cout << "The monthly budget is: " << current->pr.prioritybudget << endl;

            if (current->pr.divisionbudget != 0 || current->pr.divisionbudget != NULL)
            {
                cout << "The " << current->pr.division << "budget of each division is: " << current->pr.divisionbudget << endl;
            }

            if (current->pr.subdivisionbudget != 0 || current->pr.subdivisionbudget != NULL)
            {
                cout << "The budget of each subdivision is: " << current->pr.subdivisionbudget << endl;
            }

            current = current->next;
        }
    }

    //func to Search & Display specific priority budget 
    void SearchDisplaybudget()
    {
        
    }

    //func to Create new file 
    void FileCreation()
    {

    }

    //func to Delete existing file
    void FileDeletion()
    {

    }

};

int main()
{
    BudgetManager B;
    int budget_opt;


    //main User InterFace
    cout << "Welcome to Budget Manager!" << endl;

    do
    {

    } while(budget_opt != 10);
    
}