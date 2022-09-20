//
// Created by bia on 04/07/2022.
//

#include "IdeaRepo.h"

void IdeaRepo::readFromFile() {
    std::ifstream f("iinput.txt");

    while(!f.eof()){
        char line[500];
        std::vector<std::string> args;

        f.getline(line, 500);
        char* p = strtok(line, ",");
        while(p != nullptr){
            args.push_back((std::string) p);
            p = strtok(NULL, ",");
        }

        if(args.size() != 4)
            break;

        Idea i{args[0], args[1], args[2], std::stoi(args[3])};
        this->add(i);
    }
    f.close();
}

void IdeaRepo::WriteToFile() {
    std::ofstream f("iinput.txt");
    f.clear();

    for(auto i : this->ideas)
        f << i.getDescription() << "," << i.getStatus() << "," << i.getCreator() << "," << i.getAct() << "\n";

    f.close();
}
