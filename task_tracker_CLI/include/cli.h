//header file for CLI.cpp

#ifndef CLI_H
#define CLI_H

#include <string> 
#include <vector> 
#include <iostream> 
#include "task.h"
#include "utils.h"
#include "json.h"

class CLI
{
public:
    void addTask(const std::string& description);
    void listTasks();
    void deleteTask(int id);
    void updateTask(int id, std::string& description);
    void markInProgress(int id);
    void markDone(int id);
    void listTaskByStatus(const std::string& status);

private: 
    std::vector<Task> tasks;
    std::string jsonFile;
};

#endif //CLI_H