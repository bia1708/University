//
// Created by bia on 06/07/2022.
//

#include "Topics.h"
#include <iostream>

void TopicRepo::readFromFile() {
    std::ifstream f(R"(C:\Users\PC\Documents\GitHub\e_retake-bia1708\tinput.txt)");

    while(!f.eof()){
        char line[500];
        std::vector<std::string> args;

        f.getline(line, 500);
        char *p = strtok(line, ",");
        while(p != nullptr){
            args.push_back((std::string) p);
            p = strtok(nullptr, ",");
        }
        if(args.size() < 2)
            break;

        std::vector<User> arr;
        for(int i = 1; i < args.size(); i++){
            User u{args[i]};
            arr.push_back(u);
        }
        Topic t{args[0], arr};
        this->add(t);
    }
    f.close();
}

void TopicRepo::writeToFile() {
    std::ofstream f(R"(C:\Users\PC\Documents\GitHub\e_retake-bia1708\tinput.txt)");

    f.clear();
    for(auto el : this->topics) {
        f << el.getName();
        for(auto u : el.getUsers())
            f << "," << u.getName();
        f << "\n";
    }
    f.close();
}

std::vector<Topic> TopicRepo::getByUser(const User& u) {
    std::vector<Topic> arr;
    for(auto el : this->topics){
        int ok = 0;
        for(auto us : el.getUsers())
            if(us.getName() == u.getName())
                arr.push_back(el);
    }
    return arr;
}

void TopicRepo::update(Topic& t, const User& u) {

    std::vector<User> arr = t.getUsers();
    arr.emplace_back(u);
    t.setUsers(arr);
}
