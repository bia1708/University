//
// Created by bia on 05/07/2022.
//

#ifndef QNA_USER_H
#define QNA_USER_H

#include <string>

class User {
private:
    std::string name;
public:
    User(const std::string &name);

    const std::string &getName() const;

    void setName(const std::string &name);
};


#endif //QNA_USER_H
