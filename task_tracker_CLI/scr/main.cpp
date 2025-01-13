#include <iostream> 
#include <string>
#include <vector> 
#include "../include/cli.h"

struct CommandLineArgs { 
    std::string commnand;
    std::vector<std::string> args;
};

CommandLineArgs parseCommandLineArgs(int argc, char * argv[]);

int main(int argc, char* argv[]){ 
  CommandLineArgs args = parseCommandLineArgs(argc, argv);
  if (args.commnand.empty()){ 
    std::cout << "Error: No command entered!" << std::endl;
  }else { 
    CLI TaskManager;
    if(args.commnand == "add"){TaskManager.addTask(args.args[0]);}
    else if(args.commnand == "list" && args.args.empty()){TaskManager.listTasks();}
    else if(args.commnand == "delete"){TaskManager.deleteTask(stoi(args.args[0]));}
    else if(args.commnand == "update"){TaskManager.updateTask(stoi(args.args[0]), args.args[1]);}
    else if(args.commnand == "mark-in-progress"){TaskManager.markInProgress(stoi(args.args[0]));}
    else if(args.commnand == "mark-done"){TaskManager.markDone(stoi(args.args[0]));}
    else if(args.commnand == "list" && ! args.args.empty()){TaskManager.listTaskByStatus(args.args[0]);}
    else { std::cout << "Error: Invalid Command! Please enter a valid command!\n";}
  }
}




//Parses command line arguments
CommandLineArgs parseCommandLineArgs(int argc, char * argv[]){ 
    CommandLineArgs args;
    if (argc > 1 ){ 
        args.commnand = argv[1];
        for( int i = 2; i < argc; i++){ 
            args.args.push_back(argv[i]);
        }
    }
    return args; 
}