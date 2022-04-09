//
// Created by bia on 07/04/2022.
//
#include "Service.h"

class UI {
private:
    Service& serv;
public:
    // constructor
    explicit UI(Service &serv);

    void runApp();
    static void printMenu();
    void uiAddSchool();
    void uiPrintAll();
};

