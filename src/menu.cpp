#include "task.h"
#include "proj.h"
#include "menu.h"

char mainMenuScreen(vector<Task>& tasks, vector<Project>& projects, int taskIndex)
{
    char choice;
    const int PRIORITY_MAX = 5, COLUMN_WIDTH = 42;

    cout << endl << endl << LONG_STARLINE << endl;
    cout << "------------------------------  MAIN MENU  -------------------------------" << endl << endl;

    // Column headers
    cout << left << setw(COLUMN_WIDTH) << "------ PRIORITIZED TASKS -------" << "----- PRIORITIZED PROJECTS -----\n";

    // Get priority items
    vector<Task> priorityTasks = getPriorityTasks(tasks);
    vector<Project> priorityProjects = getPriorityProjects(projects);

    // Calculate max rows needed
    int maxRows = max(priorityTasks.size(), priorityProjects.size());
    
    // Print rows
    for(int i=0; i<maxRows; i++) {

        // Print task column
        if(i<priorityTasks.size()) {
            if(priorityTasks[i].complete) {
                cout << "[x]    ";
            } else {
                cout << "[ ]    ";
            }
            cout << i << ".  " << left << setw(COLUMN_WIDTH-11) << priorityTasks[i].title;
        } else {
            cout << setw(COLUMN_WIDTH) << "";
        }

        // Print project column
        if(i<priorityProjects.size()) {
            if(priorityProjects[i].complete) {
                cout << "[x]    ";
            } else {
                cout << "[ ]    ";
            }
            cout << (i+5) << ".  " << priorityProjects[i].title;
        }
        cout << endl;
    }

    // Display main menu
    cout << endl;
    cout << "                      [t]    View tasks" << endl;
    cout << "                      [p]    View projects" << endl;
    cout << "                      [x]    Select from priorities" << endl;
    cout << "                      [q]    Quit the program" << endl << endl;
    cout << "                      What would you like to do?: ";

    cin >> choice;
    // Input validation
    while (choice != 't' && choice != 'p' && choice != 'x' && choice != 'q') {
        cout << "Invalid choice - Please try again: ";
        cin >> choice;
    }

    return choice;
}

void inputDate(time_t& due_date)
{
    Date input;
    string dateStr;
    getline(cin, dateStr);

    if(dateStr.empty()) {
        due_date = 0;
        return;
    }

    // Parse YYYY MM DD format
    if (sscanf(dateStr.c_str(), "%d %d %d", &input.year, &input.month, &input.day) == 3) {
        if (input.isValid()) {
            tm timeInfo = {};
            timeInfo.tm_year = input.year - 1900;
            timeInfo.tm_mon = input.month - 1;
            timeInfo.tm_mday = input.day;
            due_date = mktime(&timeInfo);
            return;
        }
    }
    cout << "Invalid input - Date not recorded." << endl;
    due_date = 0;
}

string formatDate(const time_t& date) 
{
    if(date == 0) return "No due date";
    char buffer[26];
    struct tm* timeinfo = localtime(&date);
    strftime(buffer, 26, "%B %d %Y", timeinfo);
    return string(buffer);
}

void taskMenu(vector<Task>& tasks, vector<Project>& projects)
{
    // Variables
    char choice;
    int index;
    const int COLUMN_WIDTH = 20;

    cout << endl << endl << LONG_STARLINE << endl;
    cout << "------------------------------  VIEW TASKS  ------------------------------" << endl << endl;

    for(int i=0; i<tasks.size(); i++) {
        if(tasks[i].complete) {
            cout << "[x]    ";
        } else {
            cout << "[ ]    ";
        }
        cout << i << ".  " << tasks[i].title << endl;
    }

    cout << endl << "    [x]    Select a task" << endl;
    cout << "    [a]    Add a task" << endl;
    cout << "    [q]    Quit to main menu" << endl << endl;
    cout << "What would you like to do?: ";

    cin >> choice;
    // Input validation
    while(choice != 'x' && choice != 'a' && choice != 'q') {
        cout << "Invalid choice - Please try again: ";
        cin >> choice;
    }

    do {
        switch (choice) {
            case 'x': // Select a task
                cout << "Enter task number: ";
                cin >> index;
                editTask(tasks, projects, index);
                break;
            case 'a': // Add a task
                addTask(tasks, projects);
                choice = 'q';
                break;
            case 'q': // Quit to main menu
                break;
            default:
                cout << "Invalid choice - Please try again: " << endl;
                cin >> choice;
                break;
        }
    } while (choice != 'q');
}  

void projectMenu(vector<Task>& tasks, vector<Project>& projects)
{
    // Variables
    char choice;
    int index;
    const int COLUMN_WIDTH = 42;

    cout << endl << endl << LONG_STARLINE << endl;
    cout << "-----------------------------  VIEW PROJECTS  ----------------------------" << endl << endl;

    for(int i=0; i<projects.size(); i++) {
        if(projects[i].complete) {
            cout << "[x]    ";
        } else {
            cout << "[ ]    ";
        }
        cout << i << ".  " << projects[i].title << endl;
    }

    cout << endl << "    [x]    Select a project" << endl;
    cout << "    [a]    Add a project" << endl;
    cout << "    [q]    Quit to main menu" << endl << endl;
    cout << "What would you like to do?: ";

    cin >> choice;
    // Input validation
    while(choice != 'x' && choice != 'a' && choice != 'q') {
        cout << "Invalid choice - Please try again: ";
        cin >> choice;
    }

    do {
        switch (choice) {
            case 'x': // Select a project
                cout << "Enter project number: ";
                cin >> index;
                editProject(tasks, projects, index);
                choice = 'q';
                break;
            case 'a': // Add a project
                addProject(projects);
                choice = 'q';
                break;
            case 'q': // Quit to main menu
                break;
            default: 
                cout << "Invalid choice - Please try again: " << endl;
                cin >> choice;
                break;
        }
    } while (choice != 'q');
}

