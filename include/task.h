#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "proj.h"
#include "menu.h"
using namespace std;

struct Project;

struct Task 
{
    string title;
    bool complete, priority;
    string description;
    time_t due_date;
    int project_id;

    Task(string t, string desc = "", time_t dueDate = 0, int proj_id = -1)
        : title(t), description(desc), due_date(dueDate), project_id(proj_id) {}
};

void addTask(vector<Task>& tasks, vector<Project>& projects);
void deleteTask(vector<Task>& tasks, int index);
void editTask(vector<Task>& tasks, vector<Project>&projects, int taskIndex);
void printProjectTasks(const vector<Task>& tasks, const Project& project);
void linkTask(vector<int>& task_ids, int task_id);
void unlinkTask(vector<int>& task_ids, int task_id);
vector<Task> getPriorityTasks(const vector<Task>& tasks);

#endif