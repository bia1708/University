//
// Created by bia on 04/07/2022.
//

#include "Idea.h"

Idea::Idea(const std::string &description, const std::string &status, const std::string &creator, int act)
        : description(description), status(status), creator(creator), act(act) {}

const std::string &Idea::getDescription() const {
    return description;
}

void Idea::setDescription(const std::string &description) {
    Idea::description = description;
}

const std::string &Idea::getStatus() const {
    return status;
}

void Idea::setStatus(const std::string &status) {
    Idea::status = status;
}

const std::string &Idea::getCreator() const {
    return creator;
}

void Idea::setCreator(const std::string &creator) {
    Idea::creator = creator;
}

int Idea::getAct() const {
    return act;
}

void Idea::setAct(int act) {
    Idea::act = act;
}
