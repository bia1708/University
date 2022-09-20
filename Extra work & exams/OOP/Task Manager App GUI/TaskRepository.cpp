//
// Created by bia on 30/06/2022.
//

#include "TaskRepository.h"
#include <iostream>

TaskRepository::TaskRepository() {
    this->readFromFile();
}

void TaskRepository::readFromFile() {
    std::ifstream f(R"(C:\Users\PC\Documents\Facultate MegaFolder\An1\Sem2\oop files\Task Manager\taskinput.txt)");

    while(!f.eof()){
        char line[500];
        std::vector<std::string> args;

        f.getline(line, 500);

        char *p = strtok(line, ",");
        while(p != nullptr){
            args.push_back((std::string) p);
            p = strtok(nullptr, ",");
        }

        if(args.size() != 3)
            break;

        Task t{args[1], args[2], stoi(args[0])};
        this->add(t);
    }
    this->sort();
    f.close();

}

void TaskRepository::writeToFile() {
    std::ofstream f("taskinput.txt");
    f.clear();

    for(const auto& t : this->tasks)
        f << std::to_string(t.getId()) + ", " + t.getDescription() + ", " + t.getStatus() + "\n";

    f.close();
}

void TaskRepository::add(Task t) {
    if(t.getStatus() == "")
        t.setStatus("open");
    this->tasks.push_back(t);
    this->writeToFile();
    this->notify();
}

void TaskRepository::remove(int index) {
    this->tasks.erase(this->tasks.begin() + index);
    this->writeToFile();
    this->notify();
}

void TaskRepository::sort() {
    for(int i = 0; i < this->tasks.size() - 1; i++)
        for(int j = i + 1; j < this->tasks.size(); j++)
            if(this->tasks[i].getStatus() > this->tasks[j].getStatus())
                std::swap(this->tasks[i], this->tasks[j]);
}


