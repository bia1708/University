//
// Created by bia on 07/04/2022.
//

#include "UI.h"
#include <iostream>
#include <exception>

UI::UI(Service &serv) : serv(serv) {}

void UI::runApp() {
    while (true){
        printMenu();
        std::string cmd;
        std::cout << "Input: ";
        std::cin >> cmd;
        if (cmd == "1")
            uiAddSchool();
        else if (cmd == "2")
            uiPrintAll();
//        else if (cmd == "3")
//            uiClosestSchools();
        else if (cmd == "x")
            break;
    }
}

void UI::printMenu() {
    std::cout << "\n============WELCOME============\n";
    std::cout << "1. Add a new school.\n";
    std::cout << "2. Print all schools.\n";
    std::cout << "3. Show closest schools.\n";
    std::cout << "Press x to exit.\n";
}

void UI::uiAddSchool() {
    std::string name, date;
    double input;
    Address address{};

    std::cout << "Name: ";
    std::cin >> name;

    std::cout << "Address longitude: ";
    std::cin >> input;
    address.longit = input;
    std::cout << "Address latitude: ";
    std::cin >> input;
    address.lat = input;

    std::cout << "Date: ";
    std::cin >> date;

    if (this->serv.addSchool(name, address, date) != 1)
        std::cout << "School couldn't be added";
    else std::cout << "School added";
}

void UI::uiPrintAll() {
    std::vector<School> all = this->serv.getAll();
    for (int i = 0; i < all.size(); i++)
        std::cout << all[i].getOutputFormat();
}

