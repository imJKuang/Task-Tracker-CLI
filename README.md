# Task-Tracker-CLI


solution for the [task-tracker](https://roadmap.sh/projects/task-tracker)
A Trask tracker CLI that is built in c++ to function as a simple to-do list.It is usedd to track and manage tasks. 

## How to run

Clone the repository and run the following command:

```
git clone https://github.com/imJKuang/Task-Tracker-CLI.git
cd task_tracker_CLI/scr
```

Run the following command to build the project:

```bash
g++ -std=c++11 main.cpp cli.cpp json.cpp utils.cpp -o task_tracker.exe

# Adding a new task
.\task_tracker.exe add "Buy groceries"
# Output: Task added successfully (ID: 1)

# Updating and deleting tasks
.\task_tracker.exe update 1 "Buy groceries and cook dinner"
.\task_tracker.exe delete 1

# Marking a task as in progress or done
.\task_tracker.exe mark-in-progress 1
.\task_tracker.exe mark-done 1

# Listing all tasks
.\task_tracker.exe list

# Listing tasks by status
.\task_tracker.exe list done
.\task_tracker.exe list todo
.\task_tracker.exe list in-progress