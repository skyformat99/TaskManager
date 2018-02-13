cc= g++ -std=c++11
cflags= -c -Wall -I/Users/Justin/Dropbox/MyProjects/TaskManager
lflags = -L /Users/Justin/Dropbox/MyProjects/TaskManager
src= *.cpp 

all: task

task: $(src) task.h
	$(cc) $(src) -o task 

clean:
	rm task
