//
// Created by bia on 06/07/2022.
//

#ifndef E_RETAKE_BIA1708_USERREPO_H
#define E_RETAKE_BIA1708_USERREPO_H

#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include "User.h"

class UserRepo {
private:
    std::vector<User> users;
public:
    UserRepo() { this->readFromFile(); }

    void readFromFile();

    void add(const User& u) { this->users.push_back(u); }

    std::vector<User> getAll() { return this->users; }
    User getByName(std::string name);

    User& operator[](int i) { return this->users[i]; }
};


#endif //E_RETAKE_BIA1708_USERREPO_H
