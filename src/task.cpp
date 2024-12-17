#include "task.h"
#include "proj.h"
#include "menu.h"

void addTask(vector<Task>& tasks, vector<Project>& projects)
{
    // Variables
    string title, description;
    time_t due_date = 0;
    char priority;
    const int PRIORITY_MAX = 5;
    int project_id;
    cin.ignore();

    cout << endl << endl << LONG_STARLINE << endl;
    cout << "-------------------------------  ADD TASK  -------------------------------" << endl << endl;

    // Task title
    cout << "Enter title: ";
    getline(cin, title);

    // Task due date
    cout << "Enter due date as YYYY MM DD (press Enter to skip): ";
    inputDate(due_date);

    // Task description
    cout << "Enter description (press Enter to skip): ";
    getline(cin, description);
    if(description.empty()) {
        description = "No description";
    }

    Task newTask(title, description, due_date);

    // Task priority
    cout << "Is this task a priority? (y/n): ";
    cin >> priority;
    while(priority != 'y' && priority != 'n') {
        cout << "Invalid choice - Please try again (y/n): ";
        cin >> priority;
    }

    if(priority == 'y') {
        int priorityCount = 0;
        for(size_t i=0; i<tasks.size(); i++) {
            if(tasks[i].priority) {
                priorityCount++;
            }
        }
        if(priorityCount >= PRIORITY_MAX) {
            cout << "You already have 5 prioritized tasks." << endl;
        } else {
            newTask.priority = true;
        }
    }

    string project_id_str;
    cout << "Add task to project (Enter project's index or press Enter to skip): ";
    cin.ignore();
    getline(cin, project_id_str);
    if (!project_id_str.empty()) {
        int project_id = stoi(project_id_str);
        if(project_id >= 0 && project_id < projects.size()) {
            newTask.project_id = project_id;
            linkTask(projects[project_id].task_ids, tasks.size());
        }
    }
    tasks.push_back(newTask);
}

void deleteTask(vector<Task>& tasks, int index)
{
    if(index >= 0 && index < tasks.size()) {
        tasks.erase(tasks.begin() + index);
    }
}

void editTask(vector<Task>& tasks, vector<Project>& projects, int taskIndex)
{
    // Variables
    char choice;

    cout << endl << LONG_STARLINE << endl << LONG_DASHLINE << endl;
    if(tasks[taskIndex].complete) {
        cout << "       [x]  ";
    } else {
        cout << "       [ ]  ";
    }
    cout << tasks[taskIndex].title << endl;
    cout << "    ------------------------------------------------------------------    " << endl;
    cout << "       Due Date:       " << formatDate(tasks[taskIndex].due_date) << endl;
    cout << "       Priority:       ";
    if(tasks[taskIndex].priority) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    cout << "       Description:    " << tasks[taskIndex].description << endl;
    cout << LONG_DASHLINE << endl << LONG_STARLINE << endl << endl;

    if(tasks[taskIndex].complete) cout << "    [x]    Mark task uncomplete" << endl;
    else cout << "    [x]    Mark task complete" << endl;
    cout << "    [1]    Edit title" << endl;
    cout << "    [2]    Edit due date" << endl;
    cout << "    [3]    Edit description" << endl;
    if(tasks[taskIndex].priority) cout << "    [4]    Unprioritize task" << endl;
    else cout << "    [4]    Prioritize task" << endl;
    cout << "    [5]    Assign to project" << endl;
    cout << "    [6]    Delete task" << endl;
    cout << "    [q]    Quit to main menu" << endl << endl;
    cout << "What would you like to do?: ";

    cin >> choice;
    // Input validation
    while(!cin || choice != 'x' && choice != '1' && choice != '2' && choice != '3'
               && choice != '4' && choice != '5' && choice != '6' && choice != 'q') {
        cout << "Invalid input - Please try again: ";
        cin >> choice;
    }

    switch (choice) {
        case 'x': {// Mark un/complete
            if(tasks[taskIndex].complete) {
                tasks[taskIndex].complete = false;
            } else {
                tasks[taskIndex].complete = true;
            }
            choice = 'q';
            break;
        }
        case '1': { // Edit title
            cout << "Enter title: ";
            cin.ignore();
            getline(cin, tasks[taskIndex].title);
            choice = 'q';
            break;
        }
        case '2': {// Edit due date
            cout << "Enter due date (YYYY MM DD): ";
            time_t new_due_date;
            inputDate(new_due_date);
            tasks[taskIndex].due_date = new_due_date;
            choice = 'q';
            break;
        }
        case '3': { // Edit description
            cout << "Enter description:";
            getline(cin, tasks[taskIndex].description);
            choice = 'q';
            break;
        }
        case '4': { // Change priority status
            if(tasks[taskIndex].priority) {
                tasks[taskIndex].priority = false;
            } else {
                tasks[taskIndex].priority = true;
            }
            choice = 'q';
            break;
        }
        case '5': {// Assign to project
            cout << "Enter project's index: ";
            string project_id_str;
            cin.ignore();
            getline(cin, project_id_str);
            int project_id = stoi(project_id_str);
            if(project_id >= 0 && project_id < projects.size()) {
                tasks[taskIndex].project_id = project_id;
                linkTask(projects[project_id].task_ids, tasks.size());
            }
            choice = 'q';
            break;
        }
        case '6': { // Delete task
            deleteTask(tasks, taskIndex);
            choice = 'q';
            break;
        }
        case 'q': { // Quit to main menu
            choice = 'q';
            break;
        }
    }
}

vector<Task> getPriorityTasks(const vector<Task>& tasks) 
{
    vector<Task> priorityTasks;
    for(size_t i=0; i<tasks.size(); i++) {
        if(tasks[i].priority) {
            priorityTasks.push_back(tasks[i]);
        }
    }
    return priorityTasks;
}

void printProjectTasks(const vector<Task>& tasks, const Project& project) {
    cout << "       Tasks in this project:\n";
    for(size_t i=0; i<project.task_ids.size(); i++) {
        int task_id = project.task_ids[i];
        const Task& task = tasks[task_id];
        cout << (task.complete ? "       [x]    " : "       [ ]    ") << task.title << endl;
    }
}

void linkTask(vector<int>& task_ids, int task_id)
{
    task_ids.push_back(task_id);
}

void unlinkTask(vector<int>& task_ids, int task_id)
{
    task_ids.erase(remove(task_ids.begin(), task_ids.end(), task_id), task_ids.end());
} 