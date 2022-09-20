//
// Created by bia on 07/04/2022.
//

#include "Service.h"

Service::Service(Repository &repo) : repo(repo) {}

int Service::addSchool(std::string &name, struct Address address, std::string& date) {
    School school{name, address, date};
    return this->repo.add(school);
}

std::vector<School> Service::getAll() {
    return this->repo.getAllSchools();
}

