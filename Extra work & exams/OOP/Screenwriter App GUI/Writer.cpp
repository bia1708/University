//
// Created by bia on 04/07/2022.
//

#include "Writer.h"

Writer::Writer(const std::string &name, const std::string &expertise) : name(name), expertise(expertise) {}

const std::string &Writer::getName() const {
    return name;
}

void Writer::setName(const std::string &name) {
    Writer::name = name;
}

const std::string &Writer::getExpertise() const {
    return expertise;
}

void Writer::setExpertise(const std::string &expertise) {
    Writer::expertise = expertise;
}
