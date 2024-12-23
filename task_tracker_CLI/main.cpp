// This is a simple porgram that minic the way
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


using namespace std;


struct Task { 
    int taskID;
    string Task;
};



int main(){
    vector<Task> tasks;
    int choice = 0;  
    
    //function for opening the tasks.txt;
    cout<< "***************TO DO LIST********************\n";
    cout<< "*********************************************\n\n";
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
            //showTasks(); 
            break;

        case 2: 
            //addTask(); using append
            //showTasks;
            break;

        case 3: 
            //deleteTask(); uisng append
            //showTasks
            break;

        case 4: 
            //updateTask(); using append
            //showTaksks; 
            break;

        case 5: 
            choice = 5;
            break;

        default:
            cout << "Please Enter a valid option (1-5)\n";
            break;
        }

    } while(choice != 5);

    cout << "Thank you for using our J&K TO-DO-LIST SYSTEM\n";
    cout<< "*********************************************\n\n";


    return 0;
}



