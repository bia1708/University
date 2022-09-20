//
// Created by bia on 26/05/2022.
//

#include "Repository.h"


std::vector<Document> Repository::getAll() {
    return this->list;
}

void Repository::readFromFile() {
    std::ifstream f(R"(C:\Users\PC\Documents\GitHub\t3-bia1708\input.txt)");
    while(!f.eof()){
        std::string fileInput;
        std::vector<std::string> fields, keywords;
        getline(f, fileInput);
        if(fileInput != "") {
            fields = splitString(fileInput, '|');
            keywords = splitString(fields[1], ',');
            Document doc{fields[0], keywords, fields[2]};
            this->list.push_back(doc);
        }
    }
    sort();
    f.close();
}

std::vector<std::string> Repository::splitString(const std::string &s, char sep) {
    std::vector<std::string> v = {""};
    for (char c : s) {
        if (c != sep)
            v.back() += c;
        else
            v.emplace_back("");
    }
    return v;
}

std::vector<Document> Repository::filterList(const std::string &word) {
    std::vector<Document> filtered;

    for(int i = 0; i < this->list.size(); i++)
        if(this->list[i].getName().find(word) != std::string::npos)
            filtered.push_back(this->list[i]);
    return filtered;
}

void Repository::sort() {
    for(int i = 0; i < this->list.size() - 1; i++)
        for(int j = i; j < this->list.size(); j++)
            if(this->list[i].getContent().length() > this->list[j].getContent().length())
                std::swap(this->list[i], this->list[j]);
}
