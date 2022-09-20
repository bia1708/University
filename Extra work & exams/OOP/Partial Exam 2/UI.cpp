//
// Created by bia on 05/05/2022.
//

#include "UI.h"
#include <iostream>

UI::UI(Service *service) : service(*service){}


void UI::run() {
    while(true){
        this->printMenu();

        std::string cmd;
        std::cin >> cmd;

        if(cmd == "1")
            this->addCar();
        else if(cmd == "2")
            this->showAllCars();
        else if(cmd == "3")
            this->getCarsWithMaxPrice();
        else if(cmd == "4")
            this->writeToFile();
        else if(cmd == "x")
            break;
        else
            std::cout << "invalid input\n";
    }
}

void UI::printMenu() {
    std::cout << "1. Add\n";
    std::cout << "2. Print all.\n";
    std::cout << "3. Get cars with max price.\n";
    std::cout << "4. write to file\n";
}

UI::UI(const Service& service) {
    this->service = service;
}
