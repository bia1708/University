//
// Created by bia on 05/05/2022.
//

#ifndef T2_BIA1708_1_CAR_H
#define T2_BIA1708_1_CAR_H

#include "Engine.h"

class Car {
private:
    int numberOfDoors;
    Engine* engine;
public:
    Car(int numberOfDoors, Engine *engine);

    double computePrice();
    std::string toString();
};


#endif //T2_BIA1708_1_CAR_H
