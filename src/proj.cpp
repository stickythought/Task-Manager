#include "task.h"
#include "proj.h"
#include "menu.h"

void addProject(vector<Project>& projects)
{
    // Variables
    string title, description;
    time_t due_date = 0;
    char priority;
    const int PRIORITY_MAX = 5;
    cin.ignore();

    cout << endl << endl << LONG_STARLINE << endl;
    cout << "-----------------------------  ADD PROJECT  ------------------------------" << endl << endl;

    // Project title
    cout << "Enter title: ";
    getline(cin, title);

    // Project due date
    cout << "Enter due date as YYYY MM DD (press Enter to skip): ";
    inputDate(due_date);

    // Project description
    cout << "Enter description (press Enter to skip): ";
    getline(cin, description);
    if(description.empty()) {
        description = "No description";
    }

    Project newProject(title, description, due_date);

    // Project priority
    cout << "Is this project a priority? y/n: ";
    cin >> priority;
    while(priority != 'y' && priority != 'n') {
        cout << "Invalid input - Please try again (y/n): ";
        cin >> priority;
    }

    if(priority == 'y') {
        int priorityCount = 0;
        for(size_t i=0; i<projects.size(); i++) {
            if(projects[i].priority) {
                priorityCount++;
            }
        }
        if (priorityCount >= PRIORITY_MAX) {
            cout << "You already have 5 prioritized projects." << endl;
        } else {
            newProject.priority = true;
        }
    }
    projects.push_back(newProject);
}

void deleteProject(vector<Project>& projects, int index)
{
    if(index >= 0 && index < projects.size()) {
        projects.erase(projects.begin() + index);
    }
}

void editProject(vector<Task>& tasks, vector<Project>& projects, int projectIndex)
{
    // Variables
    char choice;
    time_t new_due_date;

    cout << endl << LONG_STARLINE << endl << LONG_DASHLINE << endl;
    if(projects[projectIndex].complete) {
        cout << "       [x]    ";
    } else {
        cout << "       [ ]    ";
    }
    cout << projects[projectIndex].title << endl;
    cout << "   --------------------------------------------------------------------   " << endl;
    cout << "       Due Date:       " << formatDate(projects[projectIndex].due_date) << endl;
    cout << "       Priority:       ";
    if(projects[projectIndex].priority) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    cout << "       Description:    " << projects[projectIndex].description << endl;
    cout << "    ------------------------------------------------------------------    " << endl;
    printProjectTasks(tasks, projects[projectIndex]);
    cout << LONG_DASHLINE << endl << LONG_STARLINE << endl << endl;

    if(projects[projectIndex].complete) cout << "    [x]    Mark project uncomplete" << endl;
    else cout << "    [x]    Mark project complete" << endl;
    cout << "    [1]    Edit title" << endl;
    cout << "    [2]    Edit due date" << endl;
    cout << "    [3]    Edit description" << endl;
    if(projects[projectIndex].priority) cout << "    [4]    Unprioritize project" << endl;
    else cout << "    [4]    Prioritize task" << endl;
    cout << "    [5]    Delete project" << endl;
    cout << "    [q]    Quit to main menu" << endl << endl;
    cout << "What would you like to do?: ";

    cin >> choice;
    // Input validation
    while(!cin || choice != 'x' && choice != '1' && choice != '2' && choice != '3'
               && choice != '4' && choice != '5' && choice != 'q') {
        cout << "Invalid input - Please try again: ";
        cin >> choice;
    }


    switch (choice) {
        case 'x': // Mark un/complete
            if(projects[projectIndex].complete) {
                projects[projectIndex].complete = false;
            } else {
                projects[projectIndex].complete = true;
            }
            choice = 'q';
            break;
        case '1': // Edit title
            cout << "Enter title: ";
            cin.ignore();
            getline(cin, projects[projectIndex].title);
            choice = 'q';
            break;
        case '2': // Edit due date
            cout << "Enter due date (YYYY MM DD): ";
            time_t new_due_date;
            inputDate(new_due_date);
            projects[projectIndex].due_date = new_due_date;
            choice = 'q';
            break;
        case '3': // Edit description
            cout << "Enter description:" << endl;
            cin.ignore();
            getline(cin, projects[projectIndex].description);
            choice = 'q';
            break;
        case '4': // Change priority status
            if(projects[projectIndex].priority) projects[projectIndex].priority = false;
            else projects[projectIndex].priority = true;
            choice = 'q';
        case '5': // Delete project
            deleteProject(projects, projectIndex);
            choice = 'q';
            break;
        case 'q': // Quit the program
            choice = 'q';
            break;
        default: // Error handling
        cout << "Invalid choice - Please try again: ";
        cin >> choice;
        break;
    }
}

vector<Project> getPriorityProjects(const vector<Project>& projects)
{
    vector<Project> priorityProjects;
    for(size_t i=0; i<projects.size(); i++) {
        if(projects[i].priority) {
            priorityProjects.push_back(projects[i]);
        }
    }
    return priorityProjects;
}

