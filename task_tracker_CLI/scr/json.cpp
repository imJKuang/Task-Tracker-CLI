#include "../include/json.h"

void writeTaskToJson(struct Task task, const char* filename) {
    // Read existing content
    std::ifstream file(filename);
    std::string jsonContent;
    
    if (file.is_open()) {
        // Read the entire file content
        std::stringstream buffer;
        buffer << file.rdbuf();
        jsonContent = buffer.str();
        file.close();
    }

    // If file is empty or doesn't contain a valid JSON array, initialize it
    if (jsonContent.empty() || jsonContent.find('[') == std::string::npos) {
        jsonContent = "[\n";
    }

    // Create the new task JSON
    std::string newTaskJson =
        "    {\n"
        "        \"id\": " + std::to_string(task.id) + ",\n"
        "        \"description\": \"" + task.description + "\",\n"
        "        \"status\": \"" + task.status + "\",\n"
        "        \"createdAt\": \"" + task.createdAt + "\",\n"
        "        \"updatedAt\": \"" + task.updatedAt + "\"\n"
        "    }";

    // Find the last closing bracket
    size_t endPos = jsonContent.find_last_of(']');
    
    if (endPos != std::string::npos) {
        // Remove the closing bracket temporarily
        jsonContent = jsonContent.substr(0, endPos);
        
        // Add comma if there are existing tasks
        if (jsonContent.find('{') != std::string::npos) {
            jsonContent += ",\n";
        }
        
        // Add the new task and close the array
        jsonContent += newTaskJson + "\n]";
    } else {
        // If no closing bracket was found, start fresh
        jsonContent = "[\n" + newTaskJson + "\n]";
    }

    // Write the entire content back to file
    std::ofstream fileOut(filename);
    if (fileOut.is_open()) {
        fileOut << jsonContent;
        fileOut.close();
    }
}

//Parses a JSON file and returns a vector of Task objects.
std::vector<Task> parseJsonFile(const std::string& filename) {
    std::vector<Task> tasks;

    std::ifstream file(filename);
    std::string jsonContent;
    if (file.is_open()) {
        jsonContent.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
    }

    size_t startPos = jsonContent.find('[');
    size_t endPos = jsonContent.find_last_of(']');
    if (startPos == std::string::npos || endPos == std::string::npos) {
        return tasks; // Return an empty vector if JSON is invalid
    }

    std::string tasksJson = jsonContent.substr(startPos + 1, endPos - startPos - 1);
    size_t taskStartPos = tasksJson.find('{');
    while (taskStartPos != std::string::npos) {
        size_t taskEndPos = tasksJson.find('}', taskStartPos);
        if (taskEndPos == std::string::npos) break;

        std::string taskJson = tasksJson.substr(taskStartPos, taskEndPos - taskStartPos + 1);
        Task task;

        size_t idStartPos = taskJson.find("\"id\":") + 5;
        size_t idEndPos = taskJson.find(',', idStartPos);
        task.id = std::stoi(taskJson.substr(idStartPos, idEndPos - idStartPos));

        size_t descStartPos = taskJson.find("\"description\":") + 15;
        size_t descEndPos = taskJson.find('\"', descStartPos + 1);
        task.description = taskJson.substr(descStartPos + 1, descEndPos - descStartPos - 1);

        size_t statusStartPos = taskJson.find("\"status\":") + 10;
        size_t statusEndPos = taskJson.find('\"', statusStartPos + 1);
        task.status = taskJson.substr(statusStartPos + 1, statusEndPos - statusStartPos - 1);

        size_t createdAtStartPos = taskJson.find("\"createdAt\":") + 13;
        size_t createdAtEndPos = taskJson.find('\"', createdAtStartPos + 1);
        task.createdAt = taskJson.substr(createdAtStartPos + 1, createdAtEndPos - createdAtStartPos - 1);

        size_t updatedAtStartPos = taskJson.find("\"updatedAt\":") + 13;
        size_t updatedAtEndPos = taskJson.find('\"', updatedAtStartPos + 1);
        task.updatedAt = taskJson.substr(updatedAtStartPos + 1, updatedAtEndPos - updatedAtStartPos - 1);

        tasks.push_back(task);
        taskStartPos = tasksJson.find('{', taskEndPos);
    }

    return tasks;
}
