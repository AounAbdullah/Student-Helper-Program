#include <iostream>
using namespace std;
//2023049
//Abdullah Yasin

//Priority Class which stores detail of each Priority
class Priority
{
    public:

    //members storing each detail of Priority
    string priorityname, division;
    int subdivision;
    float prioritybudget, divisionbudget, subdivisionbudget;

    //default constrcutor to initialize all members of class
    Priority()
    {
        subdivision = NULL;
        prioritybudget = NULL;
        divisionbudget = NULL;
        subdivisionbudget = NULL;
    }

    //function to set all members of the Priority Class
    void SetValues(string name, string div, int subdiv, float prbudget, float divbudget, float subdivbudget)
    {
        priorityname = name;
        division = div;
        subdivision = subdiv;
        prioritybudget = prbudget;
        divisionbudget = divbudget;
        subdivisionbudget = subdivbudget;
    }


    //func which calculates division budget of each Priority
    float Calcdivbudget()
    {
        return divisionbudget;
    }

    //func which calculates subdivision budget of each Priority
    float Calcsubdivbudget()
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
    void InsertNode(string name, string div, int subdiv, float prbudget, float divbudget, float subdivbudget)
    {
        PriorityNode* newNode = new PriorityNode;    // Create new node
        newNode->pr.SetValues(name, div, subdiv, prbudget, divbudget, subdivbudget);
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
                cout << "The " << current->pr.division << "budget of is: " << current->pr.divisionbudget << endl;
            }

            if (current->pr.subdivisionbudget != 0 || current->pr.subdivisionbudget != NULL)
            {
                cout << "The subdivison budget is: " << current->pr.subdivisionbudget << endl;
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