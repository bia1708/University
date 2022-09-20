//
// Created by bia on 05/05/2022.
//

#include "Engine.h"

double Engine::getPrice() {
    return this->basePrice;
}

Engine::Engine(const std::string &fuelType, double basePrice) : fuelType(fuelType), basePrice(basePrice) {}
