//
// Created by bia on 05/07/2022.
//

#include "Question.h"

Question::Question(int id, const std::string &text, const std::string &creator) : id(id), text(text),
                                                                                  creator(creator) {}

int Question::getId() const {
    return id;
}

void Question::setId(int id) {
    Question::id = id;
}

const std::string &Question::getText() const {
    return text;
}

void Question::setText(const std::string &text) {
    Question::text = text;
}

const std::string &Question::getCreator() const {
    return creator;
}

void Question::setCreator(const std::string &creator) {
    Question::creator = creator;
}

int Question::getAnswers() const {
    return answers;
}

void Question::setAnswers(int answers) {
    Question::answers = answers;
}
