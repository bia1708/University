//
// Created by bia on 30/06/2022.
//

#include "Programmer.h"

Programmer::Programmer(const std::string &name, int id) : name(name), id(id) {}

const std::string &Programmer::getName() const {
    return name;
}

void Programmer::setName(const std::string &name) {
    Programmer::name = name;
}

int Programmer::getId() const {
    return id;
}

void Programmer::setId(int id) {
    Programmer::id = id;
}
