//
// Created by bia on 05/05/2022.
//

#ifndef T2_BIA1708_1_TURBOENGINE_H
#define T2_BIA1708_1_TURBOENGINE_H
#include <iostream>
#include "Engine.h"

class TurboEngine : public Engine{
public:
    TurboEngine()=default;

    explicit TurboEngine(const std::string &fuelType, double basePrice);

    double getPrice() override;
    std::string toString() override;
};


#endif //T2_BIA1708_1_TURBOENGINE_H
