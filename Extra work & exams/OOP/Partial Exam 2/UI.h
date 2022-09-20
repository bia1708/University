//
// Created by bia on 05/05/2022.
//

#ifndef T2_BIA1708_1_UI_H
#define T2_BIA1708_1_UI_H
#include "Service.h"

class UI {
private:
    Service service;
public:
    explicit UI(Service *service);

    explicit UI(const Service& service);

    void run();
    void printMenu();
    void addCar();
    void showAllCars();
    void getCarsWithMaxPrice();
    void writeToFile();
};


#endif //T2_BIA1708_1_UI_H
