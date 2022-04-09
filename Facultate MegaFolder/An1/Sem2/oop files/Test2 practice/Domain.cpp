//
// Created by bia on 07/04/2022.
//

#include "Domain.h"

School::School(const std::string &name, struct Address address, const std::string &date): name(name), address(address), date(date) {}

School::School(const School &s): name(s.name), address(s.address), date(s.date){}

void School::setName(const std::string &newName) {
    this->name = newName;
}

void School::setAddress(Address newAddress) {
    this->address = newAddress;
}

void School::setDate(const std::string &newDate) {
    this->date = newDate;
}

const std::string& School::getName() const {
    return this->name;
}

struct Address School::getAddress() {
    return this->address;
}

const std::string& School::getDate() const {
    return this->date;
}

std::string School::getOutputFormat() const {
    std::string format = this->name + " | " + std::to_string(this->address.longit) + ", " + std::to_string(this->address.lat) + " | " + this->date;
    return format;
}



