#include "../include/cli.h"
#include "../include/json.h"

void CLI::addTask(const std::string& description){ 
    Task newTask;
    newTask.id = getLastId("tasks.json") + 1;
    newTask.description = description;
    newTask.status = "todo";
    newTask.createdAt = getCurrentTime();
    newTask.updatedAt = getCurrentTime();

    writeTaskToJson(newTask, "tasks.json");
}


void CLI::listTasks()
{ 
    std::cout << "List of Tasks: \n";
    std::vector<Task> tasks = parseJsonFile("tasks.json");
    for (const auto& task : tasks ){
        if (!task.description.empty()){
            std::cout << task.id << ". " << task.description << std::endl;
            std::cout << "Task status: " << task.status << std::endl;
            std::cout << "Task createdAt: " << task.createdAt <<std::endl;
            std::cout << "Task updatedAt: " << task.updatedAt << std::endl;
        } else{
            std::cout << "Task doesnt have a description!\n";
        }
    }
}

void CLI::deleteTask(int id) {
    std::vector<Task> tasks = parseJsonFile("tasks.json");
    std::vector<Task> updatedTasks;

    for (const auto& task : tasks) {
        if (task.id != id) {
            updatedTasks.push_back(task);
        }
    }

    // Rewrite the JSON file with the updated tasks
    std::ofstream fileOut("tasks.json", std::ios::trunc);
    fileOut << "[\n";
    for (size_t i = 0; i < updatedTasks.size(); ++i) {
        const auto& task = updatedTasks[i];
        fileOut << "    {\n"
                << "        \"id\": " << task.id << ",\n"
                << "        \"description\": \"" << task.description << "\",\n"
                << "        \"status\": \"" << task.status << "\",\n"
                << "        \"createdAt\": \"" << task.createdAt << "\",\n"
                << "        \"updatedAt\": \"" << task.updatedAt << "\"\n"
                << "    }";
        if (i < updatedTasks.size() - 1) fileOut << ",";
        fileOut << "\n";
    }
    fileOut << "]";
    fileOut.close();
}


void CLI::updateTask(int id, std::string& description)
{ 
    std::vector<Task> updatedTasks;
    std::vector<Task> tasks = parseJsonFile("tasks.json");
    for(auto& task : tasks){ 
        if(task.id == id){
            task.description = description;
            task.updatedAt = getCurrentTime();
            updatedTasks.push_back(task);
        }else{
            updatedTasks.push_back(task);
        }
    }
    for (const auto& task : updatedTasks){ 
        writeTaskToJson(task,"tasks.json.tmp");

        remove("tasks.json");
        rename("tasks.json.tmp","tasks.json");
    }    
}

void CLI::markInProgress(int id){
    std::vector<Task> updatedTasks;
    std::vector<Task> tasks = parseJsonFile("tasks.json");

    for(auto& task : tasks){ 
        if(task.id == id){ 
            task.status = "in-progress";\
            task.updatedAt = getCurrentTime();
            updatedTasks.push_back(task);
        }else{
            updatedTasks.push_back(task);
        }
    }
    for (const auto& task : updatedTasks){ 
        writeTaskToJson(task, "tasks.json.tmp");
    }


    remove("tasks.json");
    rename("tasks.json.tmp", "tasks.json");
}

void CLI::markDone(int id){ 
    std::vector<Task> updatedTasks;
    std::vector<Task> tasks = parseJsonFile("tasks.json");

    for(auto& task : tasks){ 
        if(task.id == id){
            task.status = "done";
            task.updatedAt = getCurrentTime();
            updatedTasks.push_back(task);
        }else{
            updatedTasks.push_back(task); 
        }
    }
    for (const auto& task : updatedTasks){ 
        writeTaskToJson(task, "tasks.json.tmp");
    }


    remove("tasks.json");
    rename("tasks.json.tmp", "tasks.json");
}
void CLI::listTaskByStatus(const std::string& status){
    std::cout << "List of " << status << "task(s)\n";
    std::vector<Task> tasks = parseJsonFile("tasks.json");
    for(const auto& task : tasks){ 
        if(task.status == status){
            std::cout << task.id << ". " << task.description << std::endl;
            std::cout << "Task status: " << task.status << std::endl;
            std::cout << "Task createdAt: " << task.createdAt <<std::endl;
            std::cout << "Task updatedAt: " << task.updatedAt << std::endl<< std::endl;
        }
    }
}
