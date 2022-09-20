//
// Created by bia on 30/06/2022.
//

#ifndef TASK_MANAGER_TASKREPOSITORY_H
#define TASK_MANAGER_TASKREPOSITORY_H
#include <vector>
#include <cstring>
#include <fstream>
#include "Task.h"
#include "Observer.h"

class TaskRepository : public Subject {
private:
    std::vector<Task> tasks;
public:
    TaskRepository();

    void readFromFile();
    void writeToFile();

    void add(Task t);
    void remove(int index);

    void sort();
    std::vector<Task> getAll() { return this->tasks; };
    Task& operator[](int index) { return this->tasks[index]; }
};


#endif //TASK_MANAGER_TASKREPOSITORY_H
