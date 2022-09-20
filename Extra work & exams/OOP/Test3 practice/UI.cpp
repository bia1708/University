//
// Created by bia on 05/05/2022.
//

#include "UI.h"

UI::UI(RealEstateAgency *service) : service(service) {}

void UI::run() {
    while(true){
        this->printMenu();

        std::string cmd;
        std::cin >> cmd;

        if(cmd == "1")
            this->removeClient();
        else if(cmd == "2"){
            this->showAllClients();
            this->showAllDwellings();
        } else if(cmd == "3")
            this->addDwelling();
        else if(cmd == "4")
            this->writeToFile();
        else if(cmd == "x")
            break;
        else
            std::cout << "Ai gresit broski, scriu in fisier?\n";
    }
}

void UI::printMenu() {

}

void UI::removeClient() {

}

void UI::showAllClients() {

}

void UI::showAllDwellings() {

}

void UI::addDwelling() {

}

void UI::showAllInterested(Dwelling d) {

}

void UI::writeToFile() {

}

