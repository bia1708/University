#include <iostream>
#include "UI.h"

int main() {
    Repository repo{};
    Service serv{repo};
    UI ui{serv};
    ui.runApp();
    return 0;
}
