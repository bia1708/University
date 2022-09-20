//
// Created by bia on 05/05/2022.
//

#include "Car.h"

double Car::computePrice() {
    double basePrice = 7000;

    if(this->numberOfDoors == 4)
        basePrice += 1500;

    basePrice += this->engine->getPrice();
    return basePrice;
}

std::string Car::toString() {
    return "Number of Doors: " + std::to_string(this->numberOfDoors) + "\n" + this->engine->toString();
}

Car::Car(int numberOfDoors, Engine *engine) : numberOfDoors(numberOfDoors), engine(engine) {}
