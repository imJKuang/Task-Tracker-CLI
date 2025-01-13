// header file of task struct.

#ifndef TASK_H
#define TASK_H



#include <string>
#include <ctime>


struct Task
{
    int id;
    std::string description;
    std::string status;
    std::string createdAt;
    std::string updatedAt;
};

#endif // TASK_H
