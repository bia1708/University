//
// Created by bia on 05/07/2022.
//

#include "AnswerRepo.h"

void AnswerRepo::readFromFile() {
    std::ifstream f(R"(C:\Users\PC\Documents\Facultate MegaFolder\An1\Sem2\oop files\QnA\ainput.txt)");

    while(!f.eof()) {
        char line[500];
        std::vector<std::string> args;

        f.getline(line, 500);

        char *p = strtok(line, ",");
        while (p != nullptr) {
            args.push_back((std::string) p);
            p = strtok(nullptr, ",");
        }

        if (args.size() != 5)
            break;

        Answer a{std::stoi(args[0]), std::stoi(args[1]), args[2], args[3], std::stoi(args[4])};
        this->add(a);
    }
//    this->sort();
    f.close();
}

void AnswerRepo::writeToFile() {
    std::ofstream f(R"(C:\Users\PC\Documents\Facultate MegaFolder\An1\Sem2\oop files\QnA\ainput.txt)");
    f.clear();

    for(auto q : this->answers)
        f << q.getId() << "," << q.getQId() << "," << q.getText() << ","  << q.getAName() << "," << q.getVotes();

    f.close();
}

std::vector<Answer> AnswerRepo::getById(int id) {
    std::vector<Answer> neww;
    for(auto a : this->answers)
        if(a.getQId() == id)
            neww.push_back(a);
    return neww;
}
