//
// Created by bia on 05/07/2022.
//

#include "UserRepo.h"

void UserRepo::readFromFile() {
    std::ifstream f(R"(C:\Users\PC\Documents\Facultate MegaFolder\An1\Sem2\oop files\QnA\uinput.txt)");

    while(!f.eof()){
        std::string name;
        f >> name;
        if(name.empty())
            break;
        User u{name};
        this->add(u);
    }
    f.close();
}
