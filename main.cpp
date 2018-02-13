#include "task.h"
//Menu that the user will see.
int main()
{
	Node *head = NULL;
	Task taskObj;
	std::string task, label;
	int priority, id;
	char choice;

	std::cout << "WELCOME. This is just a simple task manager program" << std::endl;
	readTasks(head);

	while(choice != 'q'){
		if(printTasks(head) == false){
				std::cout << "LIST IS CURRENTLY EMPTY\n\n";
			}

		std::cout << "A) Add a task\n";
		std::cout << "B) Remove a task\n";
		std::cout << "Press 'q' to exit\n";
		std::cout << "Choice: ";
		std::cin >> choice;

		if(choice == 'a'){
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Task: ";
			getline(std::cin,task);
			taskObj.setTask(task);

			std::cout << "Priority: ";
			std::cin >> priority;
			while(std::cin.fail()){
				std::cin.clear();
				std::cin.ignore();
				std::cout << "ERROR. Must be an integer value for input.\nPriority: ";
				std::cin >> priority;
				
			}
			taskObj.setPriority(priority);

			std::cout << "Label: ";
			std::cin >> label;
			taskObj.setLabel(label);
			std::cin.clear();
			std::cin.ignore();
			
			insertBasedOnPriority(head, taskObj);
			writeTasks(head);
		}
		if(choice == 'b'){
			std::cin.clear();
			std::cout << "Please enter the task ID: ";
			std::cin >> id;
			while(std::cin.fail()){
				std::cin.clear();
				std::cin.ignore();
				std::cout << "ERROR. Must be an integer value for input.\nTask ID: ";
				std::cin >> id;
				
			}

			if(removeTask(head, id)){
				std::cout << "TASK REMOVED\n";
			}
			else{
				std::cout << "COULD NOT FIND TASK\n";
			}
			writeTasks(head);
		}
	}
	deleteList(head);
	std::cout <<"CYA LATER!" << std::endl;
}
