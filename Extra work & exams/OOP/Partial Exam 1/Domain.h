//
// Created by bia on 07/04/2022.
//
#pragma once
#include <string>

struct Address{
    double longit, lat;
};

struct Date{
    int day, month, year;
};

class School {
private:
    std::string name;
    struct Date date;
    struct Address address;
    bool visited;

public:
    // constructor
    explicit School(const std::string& name = "", struct Address address = {0.0, 0.0}, struct Date date = {0, 0 , 0}, bool visited = false);

    // copy constructor
    School(const School &s);

    // setters
    void setName(const std::string& newName);
    void setAddress(Address newAddress);
    void setDate(struct Date newDate);
    void setVisited(bool newVisited);

    // getters
    const std::string& getName() const;
    struct Address getAddress();
    struct Date getDate();
    bool getVisited() const;

    // output
    std::string getOutputFormat() const;
};