// of how to-do list work. 

//version 1. 
// start from scratch, build a simple that allows
//user to add, update and delete tasks. 
//show all tasks 


//to save the tasks, i will use the write, append and read to txt.
//which is named task.txt.
//which serves the puporse of add, update and delete tasks. 


#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector> 
#include <sstream> 


using namespace std;


struct Task { 
    int taskID;
    string toDo;
};

vector<Task> processInput(const string& filename);
void showTasks(const vector<Task>& tasks);
void addTask(const string& filename, const vector<Task>& tasks );
void deleteTask(const string& filename, vector<Task>& tasks);
void  updateTask(const string& filename, vector<Task>& tasks);

int main(){



    vector<Task> tasks; 
    int choice = 0;  
    
    //function for opening the tasks.txt;
    cout<< "***************TO DO LIST********************\n";
    cout<< "*********************************************\n\n";


    tasks = processInput("tasks.txt");
    do{
        


        cout<< "Enter the option from below(1-5): \n";
        cout<< "1 - show all tasks\n";
        cout<< "2 - Add a new task\n";
        cout<< "3 - delete a task\n";
        cout<< "4 - update a task\n";
        cout<< "5 - quit\n";

        cin >> choice; 

        switch (choice)
        {
        case 1:
            showTasks(tasks); 
            break;

        case 2: 
            addTask("tasks.txt", tasks); 
            tasks = processInput("tasks.txt");
            showTasks(tasks); 
            break;

        case 3: 
            showTasks(tasks); 
            deleteTask("tasks.txt", tasks);
            showTasks(tasks);
            break;

        case 4: 
            showTasks(tasks); 
            updateTask("tasks.txt", tasks);
            showTasks(tasks);
            break;

        case 5: 
            choice = 5;
            break;

        default:
            cout << "Please Enter a valid option (1-5)\n";
            break;
        }

    } while(choice != 5);

    cout << "\nThank you for using our J&K TO-DO-LIST SYSTEM\n";
    cout<< "*********************************************\n\n";


    return 0;
}



vector<Task> processInput(const string& filename){ 
    vector<Task> tasks;
    ifstream file(filename);

    string line;


    if(!file.is_open()){ 
        cerr << "Error! the file *tasks.txt* can't be found!\n";
        return tasks; 
    }

    while (getline(file, line)){ 
        Task task;
        stringstream ss(line);
        string idStr;

        if(getline(ss, idStr, ',')){ 
            task.taskID = stoi(idStr);

            getline(ss, task.toDo);
            tasks.push_back(task);
        }
    }
    file.close();
    return tasks;
}
void showTasks(const vector<Task>& tasks){ 
    for(const auto& task : tasks){ 
        cout<< "Task #" << task.taskID << ":" << task.toDo << endl << endl; 
    }
}
void addTask(const string& filename, const vector<Task>& tasks){
    ofstream file(filename, ios::app);

    if (!file.is_open()){ 
        cout << "Can't open tasks.txt! What have you done!\n";
        return; 
    }
   
   
    int newTaskID = tasks.size() + 1; 
    string description;

    cout <<"New task ID is " << newTaskID << endl;

    cin.ignore();
    cout <<"Please enter the description of the task: ";
    getline(cin, description); 
  
    file << endl << newTaskID << "," << description; 

    file.close();

    cout << "Task added successfully!\n";
}
void deleteTask(const string& filename, vector<Task>& tasks){ 
    int taskID_Delete; 
    int newTaskId = 1;
   
   
    ofstream file(filename, ios::trunc);
    
    if (!file.is_open()){ 
        cout << "Can't open tasks.txt! What have you done!\n";
        return; 
    }



    cout << "Which task would you like to delete?";
    cin >> taskID_Delete;

    bool found = false;

    for(size_t i = 0; i < tasks.size(); i++){
        if (tasks[i].taskID == taskID_Delete){ 
            tasks.erase(tasks.begin() + i);
            found = true; 
            break;
        }
    }

    if (!found){ 
        cout << "#" << taskID_Delete << "is not found!\n";
        return;
    }


    for(const auto& task : tasks){ 
        file << newTaskId << "," << task.toDo << endl;
        newTaskId++;
    }
    file.close();

    cout << "Task deleted successfully!\n";
}

void updateTask(const string& filename, vector<Task>& tasks){ 
    int taskIDToUpdate; 

    ofstream file(filename);

    if(!file.is_open())
    { 
        cout<< "Can't open tasks.txt. What have u done!\n";
        return;
    }

    cout << "Which task would you like to modify?\n";
    cin >> taskIDToUpdate;

    bool found = false;

    for (size_t i = 0; i < tasks.size(); i++){
        if (tasks[i].taskID == taskIDToUpdate){
            cout << "Enter the new task description: ";
            cin.ignore();
            getline(cin, tasks[i].toDo);
            found = true;
            break;
        }
    }

    if(!found){ 
        cout << "please enter a valid task ID!(1-" << tasks.size() + 1 << ")" << endl;
        return;
    }

    for (const auto& task : tasks){ 
        file << task.taskID << "," << task.toDo << endl;
    }
    
    file.close();
    
    cout << "Task updated successfully!\n";
} 