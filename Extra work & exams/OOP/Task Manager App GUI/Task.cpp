//
// Created by bia on 30/06/2022.
//

#include "Task.h"

Task::Task(const std::string &description, const std::string &status, int id) : description(description),
                                                                                status(status), id(id) {}

const std::string &Task::getDescription() const {
    return description;
}

void Task::setDescription(const std::string &description) {
    Task::description = description;
}

const std::string &Task::getStatus() const {
    return status;
}

void Task::setStatus(const std::string &status) {
    Task::status = status;
}

int Task::getId() const {
    return id;
}

void Task::setId(int id) {
    Task::id = id;
}
