//
// Created by bia on 05/07/2022.
//

#ifndef QNA_USERREPO_H
#define QNA_USERREPO_H

#include "User.h"
#include <string>
#include <vector>
#include <cstring>
#include <fstream>

class UserRepo {
private:
    std::vector<User> users;
public:
    UserRepo() { this->readFromFile(); };

    void readFromFile();

    void add(const User& e) { this->users.push_back(e); };

    std::vector<User> getAll() { return this->users; };

    User& operator[](int index) { return this->users[index]; };
};


#endif //QNA_USERREPO_H
