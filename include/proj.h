#ifndef PROJ_H
#define PROJ_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include "task.h"
#include "menu.h"
using namespace std;

struct Task;

struct Project
{
    string title;
    vector<Task> tasks;
    vector<Project> projects;
    string description;
    bool complete, priority;
    time_t due_date;
    vector<int> task_ids;

    Project(string t, string desc = "", time_t dueDate = 0)
        : title(t), description(desc), due_date(dueDate) {}
};

void addProject(vector<Project>& projects);
void deleteProject(vector<Project>& projects, int index);
void editProject(vector<Task>& tasks, vector<Project>& projects, int projectIndex);
vector<Project> getPriorityProjects(const vector<Project>& projects);

#endif