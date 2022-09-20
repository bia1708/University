//
// Created by bia on 26/05/2022.
//

#ifndef T3_BIA1708_REPOSITORY_H
#define T3_BIA1708_REPOSITORY_H
#include "Document.h"
#include <fstream>

class Repository {
private:
    std::vector<Document> list;
public:
    void readFromFile();
    void sort();
    std::vector<Document> getAll();
    std::vector<std::string> splitString(const std::string& input, char sep);
    std::vector<Document> filterList(const std::string& input);
};


#endif //T3_BIA1708_REPOSITORY_H

