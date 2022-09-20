//
// Created by bia on 05/05/2022.
//

#ifndef T2_BIA1708_1_SERVICE_H
#define T2_BIA1708_1_SERVICE_H
#include <iostream>
#include <vector>
#include "Car.h"

class Service {
private:
    std::vector<Car*> cars;
public:
    Engine* createEngine(std::string engineType, std::string fuelType, int autonomy);

    explicit Service(const std::vector<Car *> &cars);
    explicit Service(Service &service);
    explicit Service() = default;

    void addCar(int numberOfDoors, std::string engineType, std::string fuelType, int autonomy);
    std::vector<Car> getCarsWithMaxPrice(double maxPrice);
    void writeToFile(std::string filename, std::vector<Car*> carsArray);
};


#endif //T2_BIA1708_1_SERVICE_H
