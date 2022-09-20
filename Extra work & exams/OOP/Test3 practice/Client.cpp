//
// Created by bia on 05/05/2022.
//

#include "Client.h"

double Client::totalIncome() {
    return this->income;
}

std::string Client::toString() {
    std::string str;
    str = "Name: " + this->name + " || Income: " + std::to_string(this->income);
    return str;
}

