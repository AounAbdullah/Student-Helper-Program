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
    float divbudget;
    float subdivbudget;


    //func which calculates division budget of each Priority
    float Calcdivbudget()
    {

    }

    //func which calculates subdivision budget of each Priority
    float Calcsubdivbudget()
    {

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
    void InsertNode()
    {

    }

    //func to Display all finalised Budget
    void Displayallbudget()
    {

    }

    //func to Search & Display specific priority budget 
    void Searchdisplaybudget()
    {

    }

    //func to Create new file 
    void Filecreation()
    {

    }

    //func to Delete existing file
    void Filedeletion()
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