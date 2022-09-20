//
// Created by bia on 05/07/2022.
//

#ifndef QNA_QUESTION_H
#define QNA_QUESTION_H

#include <string>

class Question {
private:
    int id;
    std::string text, creator;
    int answers=0;

public:
    Question(int id, const std::string &text, const std::string &creator);

    int getId() const;

    void setId(int id);

    const std::string &getText() const;

    void setText(const std::string &text);

    const std::string &getCreator() const;

    void setCreator(const std::string &creator);

    int getAnswers() const;

    void setAnswers(int answers);
};


#endif //QNA_QUESTION_H
