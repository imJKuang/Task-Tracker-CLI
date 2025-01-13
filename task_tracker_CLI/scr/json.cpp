#include "../include/json.h"

//writes a task object to a JSON file.
void writeTaskToJson(struct Task task, const char* filename){ 
    
    std::ifstream file(filename);


    std::string jsonContent;
    std::stringstream buffer;

    //read all content of the file using rdbuf(). 
    //it creates a string and save all content in a string type
    buffer <<file.rdbuf();
    jsonContent = buffer.str();

    size_t startPos = jsonContent.find_last_of('[') + 1;
    size_t endPos = jsonContent.find_last_of(']'); 

    std::string newTaskJson = 
    "\n     {\n"
    "         \"id\": " + std::to_string(task.id) + ",\n"
    "         \"description\": \"" + task.description + "\",\n"
    "         \"status\": \"" + task.status + "\",\n"
    "         \"createdAt\": \"" + task.createdAt + "\",\n"
    "         \"UpdatedAt\": \"" + task.updatedAt + "\"\n"
    "       }\n";

    if (startPos != std::string::npos && endPos != std::string::npos){ 
        jsonContent.insert(endPos, "," + newTaskJson);
    } else {
        jsonContent = "[" + newTaskJson + "]";
    }

    std::ofstream fileOut(filename, std::ios::trunc);
    fileOut << jsonContent;
    fileOut.close();
}

//Parse a  JSON file and returns a vector of a task objects
std::vector<Task> parseJsonFile(const std::string& filename){ 
    std::vector<Task> tasks;



    std::ifstream file(filename);
    std::string jsonContent;
    std::stringstream buffer;

    //read all content of the file using rdbuf(). 
    //it creates a string and save all content in a string type
    buffer <<file.rdbuf();
    jsonContent = buffer.str();
    file.close();

    size_t startPos = jsonContent.find_last_of('[') + 1;
    size_t endPos = jsonContent.find_last_of(']'); 

    if (startPos != std::string::npos && endPos != std::string::npos){
        std::string tasksJson = jsonContent.substr(startPos, endPos - startPos);

        size_t taskStartPos = 0;
        size_t taskEndPos = tasksJson.find('}');

        while (taskEndPos != std::string::npos){ 
            std::string taskJson = jsonContent.substr(startPos, endPos - startPos);

            Task task;

            //id
            size_t idStartPos = taskJson.find("\"id\": ") + 6;
            size_t idEndPos = taskJson.find(',', idStartPos);
            task.id = stoi(taskJson.substr(idStartPos, idEndPos - idStartPos)); 

            //description
            size_t descStartPos = taskJson.find("\"description\": \"") + 16;
            size_t descEndpos = taskJson.find('\"', descStartPos );
            task.description = taskJson.substr(descStartPos, descEndpos - descStartPos); 

            //status
            size_t statusStartPos = taskJson.find("\"status\": \"") + 11;
            size_t statusEndpos = taskJson.find('\"', statusStartPos );
            task.status = taskJson.substr(statusStartPos, statusEndpos - statusStartPos);

            //createdAt
            size_t createdAtStartPos = taskJson.find("\"createdAt\": \"") + 14;
            size_t createdAtEndpos = taskJson.find('\"', createdAtStartPos );
            task.createdAt = taskJson.substr(createdAtStartPos, createdAtEndpos - createdAtStartPos);  \


            //updatedAt
            size_t updatedAtStartPos = taskJson.find("\"updatedAt\": \"") + 14;
            size_t updatedAtEndpos = taskJson.find('\"', updatedAtStartPos );
            task.updatedAt = taskJson.substr(updatedAtStartPos, updatedAtEndpos - updatedAtStartPos);  

            tasks.push_back(task);
            taskStartPos = taskEndPos + 1;
            taskEndPos = tasksJson.find('}', taskStartPos);   
        }
    }

    return tasks;
}