#include "../include/cli.h"

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

void CLI::deleteTask(int id)
{ 
    std::vector<Task> updatedTasks;
    std::vector<Task> tasks = parseJsonFile("tasks.json");

    for(int i = 1; i < id; i++){
        if(i !=id){ 
            updatedTasks.push_back(tasks[i-1]);
        }
    }
    for (int i = id + 1; i <= tasks.size(); i++){ 
        tasks[i-1].id = i -1;
        updatedTasks.push_back(tasks[i-1]);
    }

    for(const auto& task : tasks){ 
        writeTaskToJson(task, "tasks.json.tmp");
    }

    remove("tasks.json");
    rename("tasks.json.tmp","tasks.json");
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
