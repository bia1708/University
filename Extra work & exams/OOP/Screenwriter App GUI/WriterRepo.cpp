//
// Created by bia on 04/07/2022.
//

#include "WriterRepo.h"

void WriterRepo::readFromFile() {
    std::ifstream f("winput.txt");

    while(!f.eof()){
        char line[500];
        std::vector<std::string> args;

        f.getline(line, 500);
        char* p = strtok(line, ",");
        while(p != nullptr){
            args.push_back((std::string) p);
            p = strtok(NULL, ",");
        }

        if(args.size() != 2)
            break;

        Writer w{args[0], args[1]};
        this->add(w);
    }
    f.close();
}
