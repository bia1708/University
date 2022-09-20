//
// Created by bia on 06/07/2022.
//

#include "Topic.h"

Topic::Topic(const std::string &name, const std::vector<User> &users) : name(name), users(users) {}

const std::string &Topic::getName() const {
    return name;
}

void Topic::setName(const std::string &name) {
    Topic::name = name;
}

const std::vector<User> &Topic::getUsers() const {
    return users;
}

void Topic::setUsers(const std::vector<User> &users) {
    Topic::users = users;
}
