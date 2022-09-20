//
// Created by bia on 05/05/2022.
//
#include "RealEstateAgency.h"

class UI {
private:
    RealEstateAgency* service;
public:
    explicit UI(RealEstateAgency *service);
    void run();
    void printMenu();
    void removeClient();
    void showAllClients();
    void showAllDwellings();
    void addDwelling();
    void showAllInterested(Dwelling d);
    void writeToFile();
};

