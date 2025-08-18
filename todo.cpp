#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
struct Task
{
    int id;
    string title;
};
void saveTasks(const vector<Task> &tasks, string filename);
void addTask(vector<Task> &tasks);
void viewSavedTasks();
void markTaskDone(vector<Task> &tasks, int id);
void loadTasks(vector<Task> &tasks, string filename);
void viewUnsavedTasks(vector<Task> &tasks);

void saveTasks(const vector<Task> &tasks, string filename)
{
    ofstream outputFile(filename);
    if (outputFile.is_open())
    {
        // File opened successfully, proceed to write
        for (const auto &task : tasks) // Iterate through each Task in the vector
        {
            outputFile << task.id << ". ";    // Write the id of the current task
            outputFile << task.title << endl; // Write the title of the current task
        }
        outputFile.close();
    }
    else
    {
        cout << "Error opening file!" << endl;
    }
}
void addTask(vector<Task> &tasks)
{
    int id;
    string title;
    cout << "Enter Task id and Task title" << endl;
    cin >> id >> title;
    Task newTask; // Create a temporary Task object
    newTask.id = id;
    newTask.title = title;
    tasks.push_back(newTask); // Add the object to the vector
    saveTasks(tasks, "Tasks.txt");
}

void viewSavedTasks()
{
    ifstream inputFile("Tasks.txt");
    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            cout << line << endl;
        }
        inputFile.close();
    }
    else
    {
        cout << "Error in opening file" << endl;
    }
}

void markTaskDone(vector<Task> &tasks, int id)
{
    ofstream outputFile("completed.txt", ios::app);
    if (outputFile.is_open())
    {
        outputFile.close();
    }
    else
    {
        cout << "Error opening file!" << endl;
    }
}

// void deleteTask(vector<Task> &tasks, int id)
// {
// }

void loadTasks(vector<Task> &tasks, string filename)
{
    ifstream inputFile(filename);

    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            stringstream ss(line);
            Task task;
            ss >> task.id;
            if (ss.peek() == ' ')
            {                // Check if there's a space after the ID
                ss.ignore(); // Skip that single space
            }
            getline(ss, task.title);
            tasks.push_back(task);
        }
        inputFile.close();
    }
    else
    {
        cout << "Error in opening file" << endl;
    }
    viewUnsavedTasks(tasks);
}
void viewUnsavedTasks(vector<Task> &tasks)
{
    cout << "-------------------list begins ---------------------" << endl;
    for (const auto &task : tasks)
    {
        cout << task.id << " " << task.title << endl;
    }
    cout << "-------------------end of list ---------------------" << endl;
}
int main()
{
    int choice = 99;
    vector<Task> tasks;
    do
    {

        cout << endl
             << endl
             << endl;
        cout << "-------ToDo list menu --------" << endl;
        cout << "1. Add a task" << endl;
        cout << "2. View all tasks" << endl;
        cout << "3. Mark task as done" << endl;
        cout << "4. Delete task" << endl;
        cout << "5. Save tasks in a file" << endl;
        cout << "6. Load Tasks from a file" << endl;
        cout << "7. View unsaved Tasks" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            addTask(tasks);
            break;
        }

        case 2:
        {
            viewSavedTasks();
            break;
        }
        case 3:
        {
            cout << " mark done" << endl;
            break;
        }
        case 4:
        {
            cout << "Delete" << endl;
            break;
        }
        case 5:
        {
            cout << "Saving ....." << endl;
            saveTasks(tasks, "Tasks.txt");
            break;
        }
        case 6:
        {
            string filename;
            cout << "Enter file name from which you want to load tasks" << endl;
            cin >> filename;
            loadTasks(tasks, filename);
            break;
        }
        case 7:
        {
            viewUnsavedTasks(tasks);
        }
        case 0:
        {
            break;
        }
        default:
        {
            cout << "Enter a valid choice" << endl;
        }
        }
    } while (choice != 0);

    return 0;
}