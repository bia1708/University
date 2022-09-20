//
// Created by bia on 30/06/2022.
//

#ifndef TASK_MANAGER_PROGRAMMERREPOSITORY_H
#define TASK_MANAGER_PROGRAMMERREPOSITORY_H
#include "Programmer.h"
#include <vector>
#include <fstream>
#include <cstring>
#include <iostream>

class ProgrammerRepository {
private:
    std::vector<Programmer> progs;
public:
    ProgrammerRepository() { this->readFromFile(); };

    void readFromFile();
    std::string getName(int id);
    std::vector<Programmer> getAll() { return this->progs; };
};


#endif //TASK_MANAGER_PROGRAMMERREPOSITORY_H
