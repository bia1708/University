//
// Created by bia on 06/07/2022.
//

#include "PostRepo.h"
#include <iostream>

void PostRepo::readFromFile() {
    std::ifstream f(R"(C:\Users\PC\Documents\GitHub\e_retake-bia1708\pinput.txt)");

    while(!f.eof()){
        char line[500];
        std::vector<std::string> args;

        f.getline(line, 500);
        char *p = strtok(line, ",");
        while(p != nullptr){
            args.push_back((std::string) p);
            p = strtok(nullptr, ",");
        }
        if(args.size() != 5)
            break;

        timestamp t{std::stoi(args[2]), std::stoi(args[3])};
        Post post{std::stoi(args[0]), args[1], t, args[4]};
        this->add(post);
    }
    this->sortMe();
    f.close();
}

void PostRepo::writeToFile() {
    std::ofstream f(R"(C:\Users\PC\Documents\GitHub\e_retake-bia1708\pinput.txt)");

    f.clear();
    for(auto el : this->posts)
        f << el.getId() << "," << el.getText() << "," << el.getDate().day << "," << el.getDate().time << "," << el.getUser() << "\n";

    f.close();
}

void PostRepo::sort(std::vector<Post> v) {
    for(int i = 0; i < v.size() - 1; i++)
        for(int j = i + 1; j < v.size(); j++)
            if(v[i].getDate().day < v[j].getDate().day || (v[i].getDate().day == v[j].getDate().day &&
                    v[i].getDate().time < v[j].getDate().time))
                std::swap(v[i],v[j]);
}

std::vector<Post> PostRepo::getByUser(User u) {
    std::vector<Post> arr;
    for(auto el : this->posts){
        if(el.getUser() == u.getName())
            arr.push_back(el);
    }
    this->sort(arr);
    return arr;
}

void PostRepo::sortMe() {
    for(int i = 0; i < this->posts.size() - 1; i++)
        for(int j = i + 1; j < this->posts.size(); j++)
            if(this->posts[i].getDate().day < this->posts[j].getDate().day || (this->posts[i].getDate().day == this->posts[j].getDate().day &&
                    this->posts[i].getDate().time < this->posts[j].getDate().time))
                std::swap(this->posts[i],this->posts[j]);
}

std::vector<Post> PostRepo::getByString(std::string str) {
    std::vector<Post> arr;
    for(auto el : this->posts){
        if(el.getText() == str)
            arr.push_back(el);
    }
    return arr;
}

void PostRepo::update(Post& p, const std::string& txt) {
    p.setText(txt);
    this->writeToFile();
//    this->notify();
}
