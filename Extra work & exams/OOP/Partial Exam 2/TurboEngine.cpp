//
// Created by bia on 05/05/2022.
//

#include "TurboEngine.h"

double TurboEngine::getPrice() {
    if (this->fuelType == "gasoline")
        return this->basePrice + 0.01 * 100;
    else if (this->fuelType == "diesel")
        return this->basePrice + 0.01 * 150;
}

std::string TurboEngine::toString() {
    return "Fuel Type: || " + this->fuelType + "Base Price: " + std::to_string(this->basePrice);
}

TurboEngine::TurboEngine(const std::string &fuelType, double basePrice) : Engine(fuelType, basePrice) {}
