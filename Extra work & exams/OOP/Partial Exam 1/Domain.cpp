//
// Created by bia on 07/04/2022.
//

#include "Domain.h"

School::School(const std::string &name, struct Address address, struct Date date, bool visited): name(name), address(address), date(date), visited(visited) {}

School::School(const School &s): name(s.name), address(s.address), date(s.date), visited(s.visited){}

void School::setName(const std::string &newName) {
    this->name = newName;
}

void School::setAddress(Address newAddress) {
    this->address = newAddress;
}

void School::setDate(Date newDate) {
    this->date = newDate;
}

const std::string& School::getName() const {
    return this->name;
}

struct Address School::getAddress() {
    return this->address;
}

struct Date School::getDate(){
    return this->date;
}

std::string School::getOutputFormat() const {
    std::string format = this->name + " | " + std::to_string(this->address.longit) + ", " + std::to_string(this->address.lat) + " | " + std::to_string(this->date.day) + \
    "." + std::to_string(this->date.month) + "." + std::to_string(this->date.year) + " | " + std::to_string(this->visited);
    return format;
}

bool School::getVisited() const {
    return this->visited;
}

void School::setVisited(bool newVisited) {
    this->visited = newVisited;
}
