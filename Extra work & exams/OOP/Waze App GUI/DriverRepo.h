//
// Created by bia on 02/07/2022.
//

#ifndef WAZE_DRIVERREPO_H
#define WAZE_DRIVERREPO_H

#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include "Driver.h"

class DriverRepo {
private:
    std::vector<Driver> drivers;
public:
    DriverRepo() { this->readFromFile(); };

    void readFromFile();
    void writeToFile();

    void add(Driver driver);

    std::vector<Driver> getAll();
    std::string getName(int index);
    Driver& operator[](int index) { return this->drivers[index]; }
};


#endif //WAZE_DRIVERREPO_H
