//
// Created by bia on 05/07/2022.
//

#ifndef QNA_ANSWER_H
#define QNA_ANSWER_H

#include <string>

class Answer {
private:
    int id, qId;
    std::string aName, text;
    int votes;
public:
    Answer(int id, int qId, const std::string &aName, const std::string &text, int votes);

    int getId() const;

    void setId(int id);

    int getQId() const;

    void setQId(int qId);

    const std::string &getAName() const;

    void setAName(const std::string &aName);

    const std::string &getText() const;

    void setText(const std::string &text);

    int getVotes() const;

    void setVotes(int votes);
};


#endif //QNA_ANSWER_H
