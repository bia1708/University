//
// Created by bia on 05/05/2022.
//

#ifndef T2_BIA1708_1_ENGINE_H
#define T2_BIA1708_1_ENGINE_H
#include <iostream>

class Engine {
protected:
    std::string fuelType;
    double basePrice = 3000;
public:
    Engine(const std::string &fuelType, double basePrice);

    virtual double getPrice();
    virtual std::string toString()=0;
};


#endif //T2_BIA1708_1_ENGINE_H
