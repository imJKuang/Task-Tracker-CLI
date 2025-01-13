#ifndef UTILS_H
#define UTILS_H


#include <string> 
#include <ctime> 
#include <chrono>
#include <vector> 
#include <iomanip>
#include "task.h"
#include "json.h"


std::string getCurrentTime();
int getLastId(const std::string& filename);


#endif //UTILS_H