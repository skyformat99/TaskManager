#include <iostream> 
#include <string> 
#include <fstream>
#include <iomanip>
#include <random>
#define SIZE 5 //Max number of subtasks each task could have 

class SubTaskQueue{
private: 
	std::string taskBuf[SIZE];
	int front;
	int index;
	bool nextIndex(int& index);
public: 
	SubTaskQueue(){front = index = 0;}
	bool insert(std::string);
	bool remove(std::string&);
	bool isFull(){return (index == SIZE);}
	bool isEmpty(){return (front == index);}
};

class Task{ 
private: 
	std::string task; 
	std::string label; //Label for different tasks. EX: Personal, Calculus etc.  
	int priority; 
	int taskID; //This data member is like a key that the user can enter to remove a task once it's done 
public: 
	SubTaskQueue subTask;
	Task();
	void setTask(std::string);
	void setPriority(int);
	void setTaskID(int);
	void setLabel(std::string); 

	std::string getTask(){return task;}
	int getPriority(){return priority;}
	int getTaskID(){return taskID;}
	std::string getLabel(){return label;}
};

class Node{
public:
	Task task;
	Node* next; 
	Node* previous;
};

bool insertBasedOnPriority(Node*&, Task);
bool printTasks(Node*);
bool removeTask(Node*&, int);
bool checkDuplication(Node*, int);
void deleteList(Node*&);
void writeTasks(Node*);
void readTasks(Node*&);
int assignID(Node*);
