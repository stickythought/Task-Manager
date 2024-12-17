#include "task.h"
#include "proj.h"
#include "menu.h"

int main() 
{
    // Variables
    char mainMenuChoice, selectTaskChoice;
    int taskIndex = -1, priorityIndex = -1;
    vector<Task> tasks;
    vector<Project> projects;

    do {
        // Display main menu
        mainMenuChoice = mainMenuScreen(tasks, projects, taskIndex);
        switch (mainMenuChoice) {
            case 't': // View tasks
                taskMenu(tasks, projects);
                break;
            case 'p': // View projects
                projectMenu(tasks, projects);
                break;
            case 'x': // Select from priority lists (User sees tasks listed as 0-4 and projects as 5-9)
                cout << "                      Enter task or project number: ";
                cin >> priorityIndex;

                if(priorityIndex >= 0 && priorityIndex< 5) { 
                    // Convert display index to vector of priority tasks and use that index
                    vector<Task> priorityTasks = getPriorityTasks(tasks);
                    if(priorityIndex < priorityTasks.size()) {
                        // Find this task in the original tasks vector
                        for(size_t i=0; i<tasks.size(); i++) {
                            if(tasks[i].title == priorityTasks[priorityIndex].title) {
                                editTask(tasks, projects, i);
                                break;
                            }
                        }
                    } else {
                        cout << "Invalid input: Selection not made." << endl;
                    }
                } else if (priorityIndex >= 5 && priorityIndex <= 9) {
                    // Convert display index to vector of priority projects and use that index
                    vector<Project> priorityProjects = getPriorityProjects(projects);
                    int projectIndex = priorityIndex - 5;
                    if (projectIndex < priorityProjects.size()) {
                        // Find this project in the original projects vector
                        for(size_t i=0; i<projects.size(); i++) {
                            if(projects[i].title == priorityProjects[projectIndex].title) {
                                editProject(tasks, projects, i);
                                break;
                            }
                        }
                    } else {
                        cout << "Invalid input: Selection not made." << endl;
                    }
                } else {
                    cout << "Invalid input: Please try again." << endl;
                }
                break;
            case 'q': // Quit the program
                break;
            default:
                cout << "Invalid choice: Please try again." << endl;
                cin >> mainMenuChoice;
                break;
        }
    } while (mainMenuChoice != 'q');
    return 0;
}