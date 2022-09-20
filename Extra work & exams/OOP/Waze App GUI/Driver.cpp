//
// Created by bia on 02/07/2022.
//

#include "Driver.h"

Driver::Driver(const std::string &name, const std::string &status, struct location &location, int score) : name(
        name), status(status), location(location), score(score) {}

const std::string &Driver::getName() const {
    return name;
}

void Driver::setName(const std::string &name) {
    Driver::name = name;
}

const std::string &Driver::getStatus() const {
    return status;
}

void Driver::setStatus(const std::string &status) {
    Driver::status = status;
}

const struct location &Driver::getLocation() const {
    return location;
}

void Driver::setLocation(const struct location &location) {
    Driver::location = location;
}

int Driver::getScore() const {
    return score;
}

void Driver::setScore(int score) {
    Driver::score = score;
}

