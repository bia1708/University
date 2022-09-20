//
// Created by bia on 05/07/2022.
//

#ifndef QNA_ANSWERREPO_H
#define QNA_ANSWERREPO_H

#include "Answer.h"
#include <string>
#include <vector>
#include <cstring>
#include <fstream>

class AnswerRepo {
private:
    std::vector<Answer> answers;
public:
    AnswerRepo() { this->readFromFile(); };

    void readFromFile();
    void writeToFile();

    void add(const Answer& a) { this->answers.push_back(a); };

    std::vector<Answer> getAll() { return this->answers; };
    std::vector<Answer> getById(int id);
    Answer& operator[](int i) { return this->answers[i]; };
};


#endif //QNA_ANSWERREPO_H
