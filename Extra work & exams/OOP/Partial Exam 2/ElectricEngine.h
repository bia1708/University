//
// Created by bia on 05/05/2022.
//

#ifndef T2_BIA1708_1_ELECTRICENGINE_H
#define T2_BIA1708_1_ELECTRICENGINE_H

#include "Engine.h"
#include <iostream>

class ElectricEngine :public Engine{
private:
    int autonomy;
public:
    ElectricEngine(const std::string &fuelType, double basePrice, int autonomy);

    double getPrice() override;
    std::string toString() override;

};


#endif //T2_BIA1708_1_ELECTRICENGINE_H
