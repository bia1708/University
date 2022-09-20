//
// Created by bia on 02/07/2022.
//

#include "ReportRepo.h"
#include <iostream>

void ReportRepo::readFromFile() {
    std::ifstream f(R"(C:\Users\PC\Documents\Facultate MegaFolder\An1\Sem2\oop files\Waze\reportsin.txt)");

    while(!f.eof()){
        char line[500];
        std::vector<std::string> args;

        f.getline(line, 500);

        char *p = strtok(line, ",");
        while(p != nullptr){
            args.emplace_back((std::string)p);
            p = strtok(nullptr, ",");
        }
        if(args.size() != 5)
            break;

        location l{std::stoi(args[2]), std::stoi(args[3])};
        bool validated;
        if(args[4] == "true")
            validated = true;
        else validated = false;
        Report r{args[0], args[1], l, validated};
        this->add(r);
    }
    f.close();
}

void ReportRepo::writeToFile() {
    std::ofstream f(R"(C:\Users\PC\Documents\Facultate MegaFolder\An1\Sem2\oop files\Waze\reportsin.txt)");
    f.clear();

    for(auto r : this->reports) {
        std::string val;
        if (r.isValidated())
            val = "true";
        else val = "false";
        f << r.getDescription() << "," << r.getReporter() << "," << r.getLocation().lat << "," << r.getLocation().lng
          << "," << val << "\n";
    }
    f.close();
}

