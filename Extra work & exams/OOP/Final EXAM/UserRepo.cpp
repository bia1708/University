//
// Created by bia on 06/07/2022.
//

#include "UserRepo.h"

void UserRepo::readFromFile() {
    std::ifstream f(R"(C:\Users\PC\Documents\GitHub\e_retake-bia1708\uinput.txt)");

    while(!f.eof()){
        std::string name;
        f >> name;
        User u{name};
        this->add(u);
    }
    f.close();
}

User UserRepo::getByName(std::string name) {
    for(auto u : this->users)
        if(u.getName() == name)
            return u;

}
