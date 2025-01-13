#include "../include/utils.h"

std::string getCurrentTime(){ 
    auto now = std::chrono::system_clock::now();
    std::time_t nowTimeT = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&nowTimeT);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%y %H:%M");
    std::string currentTime = oss.str();
    return currentTime;
}

int getLastId(const std::string& filename){ 
    int maxId = 0;
    std::vector<Task> tasks = parseJsonFile(filename);
    for (const auto& task : tasks){ 
        if(task.id > maxId){ 
            maxId = task.id;
        }
    }
    return maxId;
}
