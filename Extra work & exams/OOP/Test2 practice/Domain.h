//
// Created by bia on 07/04/2022.
//
#pragma once
#include <string>

struct Address{
    double longit, lat;
};

class School {
private:
    std::string name, date;
    struct Address address;

public:
    // constructor
    explicit School(const std::string& name = "", struct Address address = {0.0, 0.0}, const std::string& date = "");

    // copy constructor
    School(const School& s);

    // setters
    void setName(const std::string& newName);
    void setAddress(Address newAddress);
    void setDate(const std::string& newDate);

    // getters
    const std::string& getName() const;
    struct Address getAddress();
    const std::string& getDate() const;

    // output
    std::string getOutputFormat() const;
};


