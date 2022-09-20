//
// Created by bia on 30/06/2022.
//

#include "ProgrammerRepository.h"
#include <iostream>

void ProgrammerRepository::readFromFile() {
    std::ifstream f(R"(C:\Users\PC\Documents\Facultate MegaFolder\An1\Sem2\oop files\Task Manager\programmerinput.txt)");

    while(true){
        char line[500];
        std::vector<std::string> args;

        f.getline(line, 500);

        char *p = strtok(line, ",");
        while(p != nullptr){
            args.push_back((std::string) p);
            p = strtok(nullptr, ",");
        }
        if(args.size() != 2) {
            break;
        }
        Programmer prog{args[1], stoi(args[0])};
        this->progs.push_back(prog);
    }
    f.close();
}

std::string ProgrammerRepository::getName(int id) {
    for(const auto& prog : this->progs)
        if(prog.getId() == id)
            return prog.getName();
    return "";
}
