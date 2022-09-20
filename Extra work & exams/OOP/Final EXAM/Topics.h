//
// Created by bia on 06/07/2022.
//

#ifndef E_RETAKE_BIA1708_TOPICS_H
#define E_RETAKE_BIA1708_TOPICS_H

#include <vector>
#include "Topic.h"
#include "User.h"
#include "Observer.h"
#include <fstream>
#include <cstring>
#include <string>

class TopicRepo {
private:
    std::vector<Topic> topics;
public:
    TopicRepo() { this->readFromFile(); }

    void readFromFile();
    void writeToFile();

    void add(const Topic& t) { this->topics.push_back(t); }
    void update(Topic& t, const User& u);

    std::vector<Topic> getAll() { return this->topics; }
    std::vector<Topic> getByUser(const User& u);
    Topic& operator[](int i) { return this->topics[i]; };
};


#endif //E_RETAKE_BIA1708_TOPICS_H
