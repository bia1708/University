//
// Created by bia on 06/07/2022.
//

#ifndef E_RETAKE_BIA1708_TOPIC_H
#define E_RETAKE_BIA1708_TOPIC_H

#include "User.h"
#include <string>
#include <vector>

class Topic {
private:
    std::string name;
    std::vector<User> users;
public:
    Topic(const std::string &name, const std::vector<User> &users);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::vector<User> &getUsers() const;

    void setUsers(const std::vector<User> &users);
};


#endif //E_RETAKE_BIA1708_TOPIC_H
