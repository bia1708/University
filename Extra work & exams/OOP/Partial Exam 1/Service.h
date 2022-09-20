//
// Created by bia on 07/04/2022.
//
#pragma once
#include "Repository.h"
#include <string>

class Service {
private:
    Repository& repo;

public:
    // constructor
    explicit Service(Repository &repo);

    int addSchool(std::string& name, struct Address address, struct Date date, bool visited);
    int removeSchool(std::string& name, struct Address address);
    void populateList();
    std::vector<School> getAll();
};
