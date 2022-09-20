//
// Created by bia on 02/07/2022.
//

#ifndef WAZE_REPORTREPO_H
#define WAZE_REPORTREPO_H

#include "Report.h"
#include "Observer.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstring>

class ReportRepo : public Subject {
private:
    std::vector<Report> reports;
public:
    ReportRepo() { this->readFromFile(); };

    void readFromFile();
    void writeToFile();

    void add(const Report& r) { this->reports.push_back(r); this->writeToFile(); this->notify(); };
    std::vector<Report> getAll() { return this->reports; };
    Report& operator[](int index) { return this->reports[index]; }


};


#endif //WAZE_REPORTREPO_H
