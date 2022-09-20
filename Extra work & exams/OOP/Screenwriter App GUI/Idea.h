//
// Created by bia on 04/07/2022.
//

#ifndef SCREENWRITER_IDEA_H
#define SCREENWRITER_IDEA_H

#include <string>

class Idea {
public:
    std::string description, status, creator;
    int act;
private:
public:
    Idea(const std::string &description, const std::string &status, const std::string &creator, int act);

    const std::string &getDescription() const;

    void setDescription(const std::string &description);

    const std::string &getStatus() const;

    void setStatus(const std::string &status);

    const std::string &getCreator() const;

    void setCreator(const std::string &creator);

    int getAct() const;

    void setAct(int act);
};


#endif //SCREENWRITER_IDEA_H
