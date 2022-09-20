//
// Created by bia on 04/07/2022.
//

#ifndef SCREENWRITER_IDEAREPO_H
#define SCREENWRITER_IDEAREPO_H

#include "Idea.h"
#include <string>
#include <vector>
#include <fstream>
#include <cstring>

class IdeaRepo {
private:
    std::vector<Idea> ideas;
public:
    IdeaRepo() { this->readFromFile(); }

    void add(const Idea& i) { this->ideas.push_back(i); this->WriteToFile(); };

    void readFromFile();
    void WriteToFile();

    std::vector<Idea> getAll() { return this->ideas; };
    Idea& operator[](int index) { return this->ideas[index]; };
};


#endif //SCREENWRITER_IDEAREPO_H
