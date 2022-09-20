//
// Created by bia on 11/05/2022.
//

#pragma once
#include "Repository.h"
#include <iostream>

class FileRepository :public Repository {
private:
    std::string filename;
    void loadFromFile();

public:
    explicit FileRepository(const std::string& filename);
    FileRepository(const FileRepository& other);

//    FileRepository(const std::string &nameOfTheFileUsed1, const std::string &nameOfTheFileUsed,
//                   const std::string &filename);

    ~FileRepository();

//    int addEvent(const Event& eventToAdd) override;

    FileRepository& operator=(const FileRepository& other);
    void saveToFile() override;
};
