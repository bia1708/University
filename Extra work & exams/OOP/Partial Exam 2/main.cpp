//
// Created by bia on 05/05/2022.
//

#include "UI.h"

int main() {
    Service serv;
    UI ui{&serv};
    ui.run();
    return 0;
}
