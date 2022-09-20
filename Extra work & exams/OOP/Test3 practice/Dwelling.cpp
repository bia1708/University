//
// Created by bia on 05/05/2022.
//

#include "Dwelling.h"

Dwelling::Dwelling(double price, bool isProfitable) : price(price), isProfitable(isProfitable) {}

double Dwelling::getPrice() const {
    return price;
}

bool Dwelling::isProfitable1() const {
    return isProfitable;
}
