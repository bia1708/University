//
// Created by bia on 07/04/2022.
//

#include "Repository.h"

Repository::Repository() {
    std::vector<School> schoolList;
}

int Repository::add(School &school) {
    int position = find(this->schoolList, school);
    if (position != -1)
        return -1;

    this->schoolList.push_back(school);
    return 1;
}


int Repository::find(std::vector<School>thisList, const School &school) {
    for(int i = 0; i < thisList.size(); i++) {
        if (thisList[i].getName() == school.getName())
            return i;
    }
    return -1;
}

std::vector<School> Repository::getAllSchools() {
    return this->schoolList;
}

int Repository::repoSize() {
    return this->schoolList.size();
}

Repository::~Repository() {
    this->schoolList.clear();
}

