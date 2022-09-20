//
// Created by bia on 07/04/2022.
//

#include "Service.h"

Service::Service(Repository &repo) : repo(repo) {}

int Service::addSchool(std::string& name, struct Address address, struct Date date, bool visited) {
    School school{name, address, date, visited};
    return this->repo.add(school);
}

int Service::removeSchool(std::string& name, struct Address address){
    Date date = {0, 0, 0};
    School school{name, address, date, 0};
    return this->repo.remove(school);
}

std::vector<School> Service::getAll() {
    return this->repo.getAllSchools();
}

void Service::populateList(){
    Address address = {12.4, 34.3};
    std::string name = "Name1";
    Date date = {12, 12, 2022};
    this->addSchool(name, address, date, 1);
    name = "Name2";
    this->addSchool(name, address, date, 1);
    name = "Name3";

    this->addSchool(name, address, date, 1);
    name = "Name4";

    this->addSchool(name, address, date, 1);
    name = "Name5";

    this->addSchool(name, address, date, 1);
}
