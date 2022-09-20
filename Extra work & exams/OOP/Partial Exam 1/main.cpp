//
// Created by bia on 07/04/2022.
//
#include "UI.h"

int main() {
    Repository repo{};
    Service serv{repo};
    serv.populateList();
    UI ui{serv};
    ui.runApp();
    return 0;
}

