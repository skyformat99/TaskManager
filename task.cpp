#include "task.h"
#define MAX_ITEM 15 //Keeping it at maximum of 15 tasks for now, but can change to accomodate more

Task::Task(){
	task = "N/A";
	label = "N/A";
	priority = 0;
	taskID = 0;
}
void Task::setTask(std::string task){
	this->task = task;
}

void Task::setPriority(int priority){
	this->priority = priority;
}

void Task::setLabel(std::string label){
	this->label = label;
}
bool checkDuplication(Node* head, int idNum){
	Node* tmp = NULL;
	for(tmp = head; tmp; tmp = tmp->next){
		if(idNum == tmp->task.getTaskID()){
			return true;
		}
	}
	return false;
}

int assignID(Node* head){
	bool found = true;
	int id = 0;
	while(found){
		srand(time(0));
		id = random() % MAX_ITEM; 
		found = checkDuplication(head, id);	
	}
	return id;
}

void Task::setTaskID(int ID){
	taskID = ID;
}

bool insertBasedOnPriority(Node* &head, Task task){
	Node *newNode = new Node; 
	Node *previousNode = NULL;
	Node *nextNode = head;
	
	//Checks if a new Node isn't created
	if(!newNode){
		return false;
	}

	newNode->task.setTask(task.getTask());
	newNode->task.setPriority(task.getPriority());
	newNode->task.setLabel(task.getLabel());
	
	//Condition to check whether we have a new task object 
	//OR it's a task that we're reading from the textfile. 
	if(task.getTaskID() != 0){
		newNode->task.setTaskID(task.getTaskID());
	}
	else{
		newNode->task.setTaskID(assignID(head));
	}

	if(!head){ //If it's an empty list
		head = newNode;
		newNode->next = NULL;
		newNode->previous = NULL;
	}
	else{
		//Traverse the list and check if the new Node's priority is greater than or equal than the next 
		//task's priority. The higher priority will always be on top. 
		while(nextNode && newNode->task.getPriority() >= nextNode->task.getPriority()){
			previousNode = nextNode;
			nextNode = nextNode->next; 
		}
		newNode->next = nextNode;
		newNode->previous = previousNode;
		if(previousNode){
			previousNode->next = newNode;
		}
		else{
			head = newNode; //If the newNode is the highest priority compared to the rest in the list 
		}
	}

	return true;
}

bool printTasks(Node* head){
	 Node* tmp = head;
	 if(!head){
	 	return false;
	 }
	 else{
		 for(tmp = head; tmp; tmp = tmp->next){
		 	std::cout << "ID: " << std::setw(5) << " " << tmp->task.getTaskID() 
					<< std::setw(5) << " "<<" Priority: " 
					<< std::setw(5) << " "  << tmp->task.getPriority()
		 			<< std::setw(5) << " "<< " Label: " << tmp->task.getLabel() 
		 			<< std::setw(5) << " "<< " Task: " << tmp->task.getTask() 
					<< std::endl << std::endl;
		 }
	}
	 return true;
}

bool removeTask(Node* &head, int taskID){
	Node* tmp = head;
	Node* previous = NULL;

	//If the list is empty, tmp will point to NULL already
	//Was previously !tmp->next, but this condition checks if a second node exists! 
	if(!tmp){
		return false;
	}

	//traverse the list till the taskIDs matches 
	while(tmp && tmp->task.getTaskID() != taskID){
		//Returns false once it reaches the end of the list and still haven't found the matching task ID
		if(!tmp->next){
			return false;
		}
		previous = tmp;
		tmp = tmp->next;
		
	}

	//deletes the chosenNode in the list and connects the list back again. 
	//Previous will only be null if we didn't traverse. 
	//through the list i.e the node being removed is the first node on the list
	if(previous){
		//Seg fault kept happening cause we assumed that the tmp->next is pointing to a node
		//BUT if tmp is the SECOND TO THE LAST NODE, tmp->next is pointing to NULL 
		
		//This checks if tmp->next exists and connects the previous node to the next node after tmp.
		if(tmp->next){
			//Assigns the next Node's pointer to the previous Node before Tmp
			tmp->next->previous = previous; 		
			previous->next = tmp->next;	
			delete tmp;
			tmp = previous;
		}
		//Otherwise if tmp->next doesn't exist, then we delete tmp, 
		//then make previous->next point to NULL
		else{
			delete tmp;
			tmp = previous;
			previous->next = NULL;
		}
	}
	//If the Node being deleted is the first Node in the list. 
	//This also checks if there's actually more than one node in the list
	else if(head->next){ 
		tmp = head->next;
		tmp->previous = NULL; //The second Node's previous was pointing to first, now NULL after delete 
		delete head;
		head = tmp;	
	}
	else{ //If it's the only Node on the list and/or the last node on the list 
		delete head;
		head = NULL;
	}
	return true;
}

void deleteList(Node*& head){
	Node* tmp = head;
	//Will keep looping until tmp becomes null
	while(tmp){
		tmp = head->next;
		delete head;
		head = tmp;	
	}		
}

//Function that will write the tasks from the linked list to a textfile
void writeTasks(Node* head){
	std::ofstream output("taskList.txt");

	output << "Priority " << std::setw(5)  << " | " << std::setw(15) << " Label  " 
		<< std::setw(15) << " | " << std::setw(15) << " ID "
		<< std::setw(15) << " | " << std::setw(15) << " Task\n ";
	output << std::setfill('-') << std::setw(100) << "\n";

	for(Node* tmp = head; tmp; tmp = tmp->next){
		//Where we'll write the nodes to the file		
		output << tmp->task.getPriority();
		output << std::setfill(' ') << std::setw(25); 
		output << tmp->task.getLabel(); 
		output << std::setfill(' ') << std::setw(30);
		output << tmp->task.getTaskID() ;
	      	output << std::setfill(' ') << std::setw(40);
		output << tmp->task.getTask() << std::endl; 
	}
	output.close();
}

//Reads the textfile and puts them into a list
void readTasks(Node* &head){
	std::ifstream fileIn("taskList.txt");
	int priority, id;
	Task tmpObj;
	std::string label, task, garbage;
	if(!fileIn.is_open()){
		return;
	}

	getline(fileIn, garbage);	
	getline(fileIn, garbage);	

	while(fileIn >> priority){
		fileIn >> label;
		fileIn >> id; 
		getline(fileIn, task);

		tmpObj.setPriority(priority);
		tmpObj.setLabel(label);
		tmpObj.setTaskID(id);
		tmpObj.setTask(task);

		insertBasedOnPriority(head, tmpObj);
	}
}


//***********************IGNORE THESE FUNCTIONS FOR NOW**********************
//----------------------------------------------------------------------------
bool SubTaskQueue::nextIndex(int& index){
	if(isFull()){
		std::cout << "QUEUE FULL" << std::endl;
		return false;
	}
	index++;
	return true;
}

bool SubTaskQueue::insert(std::string task){
	if(isFull()){
		return false;
	}
	taskBuf[index] = task;

	if(nextIndex(index)){
		return true;
	}
	else{
		index = 0;
		return false;
	}
}

bool SubTaskQueue::remove(std::string & task){
	if(isEmpty()){
		return false;
	}
	task = taskBuf[front];	

	if(nextIndex(front)){ 
		return true;	
	}
	else{ //if the front reaches the end of the array
		front = 0; //Sets front to the first element of array again
		return false;
	}
}
