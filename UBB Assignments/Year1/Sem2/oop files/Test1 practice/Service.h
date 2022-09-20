//
// Created by bia on 06/04/2022.
//
#pragma once
#include "Repository.h"
#include <string>

class Service {
private:
    Repository& repo;

public:
    // constructor
    Service(Repository &repo);

    int addPlayer(std::string& name, std::string& nationality, std::string& team, int goals);
};

