//
// Created by bia on 05/05/2022.
//

#include "Service.h"
#include "ElectricEngine.h"
#include "TurboEngine.h"
#include <fstream>

void Service::writeToFile(std::string filename, std::vector<Car*> carsArray) {
    std::ofstream file(filename);
    for(auto & car : carsArray)
        file << car->toString() << "\n";
}


void Service::addCar(int numberOfDoors, std::string engineType, std::string fuelType, int autonomy) {
    Engine *engine = this->createEngine(engineType, fuelType, autonomy);
    Car car(numberOfDoors, engine);
    this->cars.push_back(&car);
}

Engine* Service::createEngine(std::string engineType, std::string fuelType, int autonomy) {
    if (engineType == "Turbo") {
        Engine *engine = new TurboEngine(fuelType, 3000);
        return engine;
    }
    else {
//        ElectricEngine *engine = new ElectricEngine{engineType, fuelType, autonomy};
        ElectricEngine *engine = new ElectricEngine(fuelType, 3000, autonomy);
        return engine;
    }
}

std::vector<Car> Service::getCarsWithMaxPrice(double maxPrice) {
    return std::vector<Car>();
}

Service::Service(const std::vector<Car *> &cars) : cars(cars) {}

Service::Service(Service &service) {
    this->cars = service.cars;
}


