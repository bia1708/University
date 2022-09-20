//
// Created by bia on 07/04/2022.
//
#pragma once
#include "Domain.h"
#include <vector>
#include <iostream>

class Repository {
private:
    std::vector<School> schoolList;

public:
    // constructor
    Repository();

    // destructor
    virtual ~Repository();

    int add(School& school);
    int remove(School& school);
    static int find(std::vector<School>thisList, School& school);
    std::vector<School> getAllSchools();
    int repoSize();
};