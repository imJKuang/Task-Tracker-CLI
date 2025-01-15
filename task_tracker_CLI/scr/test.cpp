#include <iostream> 
#include <vector> 
#include "../include/json.h"
#include "../include/task.h"

using namespace std;

int main(){
    vector<Task> tasks = parseJsonFile("tasks.json"); 

    for(auto& task : tasks ){ 
        cout << task.id <<  ". " << task.description << endl;
            cout << "Task status: " << task.status << endl;
            cout << "Task createdAt: " << task.createdAt << endl;
            cout << "Task updatedAt: " << task.updatedAt << endl;
            cout << endl;
    }

return 0; 
}