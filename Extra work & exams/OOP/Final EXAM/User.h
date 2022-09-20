//
// Created by bia on 06/07/2022.
//

#ifndef E_RETAKE_BIA1708_USER_H
#define E_RETAKE_BIA1708_USER_H

#include <string>

class User {
private:
    std::string name;
public:
    User(const std::string &name);

    const std::string &getName() const;

    void setName(const std::string &name);
};


#endif //E_RETAKE_BIA1708_USER_H
