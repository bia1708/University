//
// Created by bia on 05/07/2022.
//

#include "QuestionRepo.h"

void QuestionRepo::readFromFile() {
    std::ifstream f(R"(C:\Users\PC\Documents\Facultate MegaFolder\An1\Sem2\oop files\QnA\qinput.txt)");

    while(!f.eof()) {
        char line[500];
        std::vector<std::string> args;

        f.getline(line, 500);

        char *p = strtok(line, ",");
        while (p != nullptr) {
            args.push_back((std::string) p);
            p = strtok(nullptr, ",");
        }

        if (args.size() != 3)
            break;

        Question q{std::stoi(args[0]), args[1], args[2]};
        this->add(q);
    }
    this->sort();
    f.close();
}

void QuestionRepo::writeToFile() {
    std::ofstream f(R"(C:\Users\PC\Documents\Facultate MegaFolder\An1\Sem2\oop files\QnA\qinput.txt)");
    f.clear();

    for(auto q : this->questions)
        f << q.getId() << "," << q.getText() << "," << q.getCreator();

    f.close();
}

void QuestionRepo::sort() {
    for(int i = 0; i < this->questions.size() - 1; i++)
        for(int j = i + 1; j < this->questions.size(); j++)
            if(this->questions[i].getAnswers() < this->questions[j].getAnswers())
                std::swap(this->questions[i], this->questions[j]);
}
