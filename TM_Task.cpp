#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Task
{
private:
    string taskname;
    int task_priority;
    string deadline;
    bool is_completed;

public:
    Task() {};
    Task(string taskname, int task_priority, string deadline, bool is_completed)
    {
        this->taskname = taskname;
        this->task_priority = task_priority;
        this->deadline = deadline;
        this->is_completed = is_completed;
    }

    // getter functions
    string getname() const
    {
        return taskname;
    }
    int getPriority() const
    {
        return task_priority;
    }
    string getDeadline() const
    {
        return deadline;
    }
    bool getCompletionStatus() const
    {
        return is_completed;
    }

    // setter functions

    void setname(const std::string &name)
    {
        taskname = name;
    }
    void setPriority(int priority)
    {
        task_priority = priority;
    }
    void setDeadline(const std::string &deadline)
    {
        this->deadline = deadline;
    }
    void setCompletionStatus(bool status)
    {
        is_completed = status;
    }

    bool task_completion()
    {
        return true;
    }

    void update_task(string &name, int priority, string &deadline)
    {
        taskname = name;
        task_priority = priority;
        this->deadline = deadline;
    }

    //used for saving information
    string serialize() const
    {
        return taskname + "," + std::to_string(task_priority) + "," + deadline + "," + (is_completed ? "1" : "0");
    }

    //retrieving information from the file
    static Task deserialize(const string &serializedTask)
    {
        // Assuming the format is "taskname,priority,deadline,isCompleted,category"
        stringstream ss(serializedTask);
        string name, deadline, category, completedStr;
        int priority;
        bool completed;

        getline(ss, name, ',');
        ss >> priority;
        getline(ss, deadline, ',');
        ss >> completedStr;
        completed = (completedStr == "1");
       

        return Task(name, priority, deadline, completed);
    }
};