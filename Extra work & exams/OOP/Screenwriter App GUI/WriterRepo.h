//
// Created by bia on 04/07/2022.
//

#ifndef SCREENWRITER_WRITERREPO_H
#define SCREENWRITER_WRITERREPO_H

#include "Writer.h"
#include <string>
#include <vector>
#include <fstream>
#include <cstring>

class WriterRepo {
private:
    std::vector<Writer> writers;
public:
    WriterRepo() { this->readFromFile(); }

    void add(const Writer& w) { this->writers.push_back(w); };

    void readFromFile();

    std::vector<Writer> getAll() { return this->writers; };
    Writer& operator[](int index) { return this->writers[index]; }
};


#endif //SCREENWRITER_WRITERREPO_H
