//
// Created by bia on 30/06/2022.
//

#ifndef TASK_MANAGER_PROGRAMMER_H
#define TASK_MANAGER_PROGRAMMER_H
#include <string>

class Programmer {
private:
    std::string name;
    int id;

public:
    Programmer(const std::string &name, int id);

    const std::string &getName() const;

    void setName(const std::string &name);

    int getId() const;

    void setId(int id);
};


#endif //TASK_MANAGER_PROGRAMMER_H
