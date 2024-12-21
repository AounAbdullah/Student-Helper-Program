#include <iostream>
#include "TM_Task.cpp"
using namespace std;

class Node
{
public:
    Task value;
    Node *next;
    Node *pre;

    Node(Task value)
    {
        this->value = value;
        next = nullptr;
        pre = nullptr;
    }
};

class LinkedList
{
public:
    Node *head;
    Node *tail;
    int length;

    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }
    void print()
    {
        Node *temp = head;
        while (temp)
        {
            cout << "Task Name: " << temp->value.getname() << ", ";
            cout << "Priority: " << temp->value.getPriority() << ", ";
            cout << "Deadline: " << temp->value.getDeadline() << ", ";
            cout << "Completed: " << (temp->value.getCompletionStatus() ? "Yes" : "No") << endl;
            temp = temp->next;
        }
        cout << endl;
    }
    void append(Task value)
    {
        Node *newnode = new Node(value);
        if (head == nullptr)
        {
            head = newnode;
            tail = newnode;
        }
        else
        {
            tail->next = newnode;
            newnode->pre = tail;
            tail = newnode;
        }
        length++;
    }
    void deletelast()
    {
        if (length == 0)
        {
            return;
        }
        Node *temp = tail;
        if (length == 1)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            tail = tail->pre;
            tail->next = nullptr;
        }
        delete temp;
        length--;
    }

    void prepend(Task value)
    {
        Node *newnode = new Node(value);
        if (head == nullptr)
        {
            head = newnode;
            tail = newnode;
        }
        else
        {
            newnode->next = head;
            head->pre = newnode;
            head = newnode;
        }
        length++;
    }

    Node *get(int index)
    {
        if (index < 0 || index > length)
        {
            return nullptr;
        }
        Node *temp = head;
        if (index < length / 2)
        {
            for (int i = 0; i < index; i++)
            {
                temp = temp->next;
            }
        }
        else
        {
            temp = tail;
            for (int i = length - 1; i > index; i--)
            {
                temp = temp->pre;
            }
        }
        return temp;
    }

    void deletefirst()
    {
        if (length == 0)
        {
            return;
        }
        Node *temp = head;
        if (length == 1)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            head = head->next;
            head->pre = nullptr;
        }
        delete temp;
        length--;
    }

    bool set(int index, Task value)
    {
        if (index < 0 || index > length)
        {
            return false;
        }
        Node *temp = get(index);
        temp->value = value;
        return true;
    }

    bool insert(int index, Task value)
    {
        Node *newnode = new Node(value);
        if (index < 0 || index > length)
        {
            return false;
        }
        if (index == 0)
        {
            prepend(value);
            return true;
        }
        if (index == length)
        {
            /* code */
            append(value);
            return true;
        }
        Node *bef = head;
        for (int i = 0; i < index - 1; i++)
        {
            bef = bef->next;
        }
        Node *temp = bef->next;
        newnode->next = temp;
        newnode->pre = bef;
        bef->next = newnode;
        temp->pre = newnode;
        length++;
        return true;
    }

    void deletenode(int index)
    {
        if (index < 0 || index > length)
        {
            return;
        }
        if (head == nullptr)
        {
            return;
        }
        if (index == 0)
        {
            return deletefirst();
        }
        if (index == length)
        {
            return deletelast();
        }
        Node *temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
       
        temp->next->pre = temp->pre;
        temp->pre->next = temp->next;
        delete temp;
        length--;
    }

    bool removeByName(const std::string &taskName)
    {
        Node *temp = head;
        while (temp)
        {
            if (temp->value.getname() == taskName)
            {
                if (temp == head)
                {
                    deletefirst();
                }
                else if (temp == tail)
                {
                    deletelast();
                }
                else
                {
                    temp->pre->next = temp->next;
                    temp->next->pre = temp->pre;
                    delete temp;
                    length--;
                }
                return true;
            }
            temp = temp->next;
        }
        return false; // Task not found
    }

    int size()
    {
        return length;
    }
};