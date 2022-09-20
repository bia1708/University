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
            uiDeleteSchool();
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
    std::cout << "1. Delete a school.\n";
    std::cout << "2. Print all schools.\n";
    std::cout << "3. Show closest schools.\n";
    std::cout << "Press x to exit.\n";
}

void UI::uiDeleteSchool() {
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

    if (this->serv.removeSchool(name, address) != 1)
        std::cout << "School couldn't be deleted";
    else std::cout << "School deleted";
}

void UI::uiPrintAll() {
    std::vector<School> all = this->serv.getAll();
    for (int i = 0; i < all.size(); i++)
        std::cout << all[i].getOutputFormat();
}
