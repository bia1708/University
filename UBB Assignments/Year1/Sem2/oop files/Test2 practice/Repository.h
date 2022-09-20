//
// Created by bia on 07/04/2022.
//

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
    static int find(std::vector<School>thisList, const School& school);
    std::vector<School> getAllSchools();
    int repoSize();
};