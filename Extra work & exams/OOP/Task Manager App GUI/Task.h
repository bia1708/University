//
// Created by bia on 30/06/2022.
//

#ifndef TASK_MANAGER_TASK_H
#define TASK_MANAGER_TASK_H
#include <string>

class Task {
private:
    std::string description, status;
    int id;
public:
    Task(const std::string &description, const std::string &status, int id);

    const std::string &getDescription() const;

    void setDescription(const std::string &description);

    const std::string &getStatus() const;

    void setStatus(const std::string &status);

    int getId() const;

    void setId(int id);
};


#endif //TASK_MANAGER_TASK_H
