//
// Created by bia on 05/05/2022.
//
#include <iostream>
#include "Dwelling.h"

class Client {
protected:
    std::string name;
    double income;
public:
    virtual double totalIncome();
    virtual std::string toString();
    virtual bool isInterested(Dwelling d)=0;

    const std::string &getName() const;

    double getIncome() const;
};

const std::string &Client::getName() const {
    return name;
}

double Client::getIncome() const {
    return income;
}
