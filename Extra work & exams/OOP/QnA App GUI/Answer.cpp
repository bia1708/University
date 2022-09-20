//
// Created by bia on 05/07/2022.
//

#include "Answer.h"

Answer::Answer(int id, int qId, const std::string &aName, const std::string &text, int votes) : id(id), qId(qId),
                                                                                                aName(aName),
                                                                                                text(text),
                                                                                                votes(votes) {}

int Answer::getId() const {
    return id;
}

void Answer::setId(int id) {
    Answer::id = id;
}

int Answer::getQId() const {
    return qId;
}

void Answer::setQId(int qId) {
    Answer::qId = qId;
}

const std::string &Answer::getAName() const {
    return aName;
}

void Answer::setAName(const std::string &aName) {
    Answer::aName = aName;
}

const std::string &Answer::getText() const {
    return text;
}

void Answer::setText(const std::string &text) {
    Answer::text = text;
}

int Answer::getVotes() const {
    return votes;
}

void Answer::setVotes(int votes) {
    Answer::votes = votes;
}
