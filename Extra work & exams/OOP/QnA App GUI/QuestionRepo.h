//
// Created by bia on 05/07/2022.
//

#ifndef QNA_QUESTIONREPO_H
#define QNA_QUESTIONREPO_H

#include "Question.h"
#include "Observer.h"
#include <string>
#include <vector>
#include <cstring>
#include <fstream>

class QuestionRepo : public Subject {
private:
    std::vector<Question> questions;
public:
    QuestionRepo() { this->readFromFile(); };

    void readFromFile();
    void writeToFile();

    void add(const Question& q) { this->questions.push_back(q); this->notify(); };

    void sort();

    std::vector<Question> getAll() { return this->questions; };
    Question& operator[](int index) { return this->questions[index]; };
};


#endif //QNA_QUESTIONREPO_H
