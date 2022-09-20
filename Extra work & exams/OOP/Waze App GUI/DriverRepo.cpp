//
// Created by bia on 02/07/2022.
//

#include "DriverRepo.h"
#include <iostream>

void DriverRepo::readFromFile() {
    std::ifstream f(R"(C:\Users\PC\Documents\Facultate MegaFolder\An1\Sem2\oop files\Waze\driversin.txt)");

    while(!f.eof()){
        char line[500];
        std::vector<std::string> args;

        f.getline(line, 500);
        char *p = strtok(line, ",");
        while(p != nullptr){
            args.emplace_back((std::string)p);
            p = strtok(nullptr, ",");
        }
        if(args.size() != 5)
            break;

        location l{std::stoi(args[2]), std::stoi(args[3])};
        Driver d{args[0], args[1], l, std::stoi(args[4])};
        this->add(d);
    }
    f.close();
}

void DriverRepo::writeToFile() {
    std::ofstream f(R"(C:\Users\PC\Documents\Facultate MegaFolder\An1\Sem2\oop files\Waze\driversin.txt)");
    f.clear();

    for(auto r : this->drivers) {
        f << r.getName() << "," << r.getStatus() << "," << r.getLocation().lat << "," << r.getLocation().lng
          << "," << r.getScore() << "\n";
    }
    f.close();
}

void DriverRepo::add(Driver driver) {
    this->drivers.emplace_back(driver);
}

std::vector<Driver> DriverRepo::getAll() {
    return this->drivers;
}

std::string DriverRepo::getName(int index) {
    return this->drivers[index].getName();
}
