//
// Created by bia on 05/07/2022.
//

#include "User.h"

User::User(const std::string &name) : name(name) {}

const std::string &User::getName() const {
    return name;
}

void User::setName(const std::string &name) {
    User::name = name;
}
