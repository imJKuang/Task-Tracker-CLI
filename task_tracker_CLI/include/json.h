// header file for write and parse the json file 

#ifndef JSON_H
#define JSON_H

#include <fstream>
#include "cli.h"
#include <vector>

void writeTaskToJson(struct Task task, const char* filename);
std::vector<Task> parseJsonFile(const std::string& filename);

#endif // JSON_H
