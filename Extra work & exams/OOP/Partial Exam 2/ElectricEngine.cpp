//
// Created by bia on 05/05/2022.
//

#include "ElectricEngine.h"

double ElectricEngine::getPrice() {
    return this->basePrice + this->autonomy * 0.01;
}

std::string ElectricEngine::toString() {
    return "Fuel Type: || " + this->fuelType + "Base Price: " + std::to_string(this->basePrice) + "Autonomy: " +
            std::to_string(this->autonomy);
}

ElectricEngine::ElectricEngine(const std::string &fuelType, double basePrice, int autonomy) : Engine(fuelType,
                                                                                                     basePrice),
                                                                                              autonomy(autonomy) {}
