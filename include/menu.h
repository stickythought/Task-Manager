#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

struct Task;
struct Project;

struct Date {
    int year, month, day;

    bool isValid() const {
        if(year < 1900 || month < 1 || month > 12 || day < 1 || day > 31) return false;
        return true;
    }
};

// Function prototypes
char mainMenuScreen(vector<Task>& tasks, vector<Project>& projects, int taskIndex);
void taskMenu(vector<Task>& tasks, vector<Project>& projects);
void projectMenu(vector<Task>& tasks, vector<Project>& projects);
void inputDate(time_t& due_date);
string formatDate(const time_t& date);

const string LONG_STARLINE = "**************************************************************************";
const string LONG_DASHLINE = "--------------------------------------------------------------------------";

#endif