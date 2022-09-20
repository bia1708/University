//
// Created by bia on 30/06/2022.
//

#ifndef TASK_MANAGER_OBSERVER_H
#define TASK_MANAGER_OBSERVER_H


#include <vector>

class Observer {
public:
    virtual void update() = 0;
};

class Subject {
private:
    std::vector<Observer*> list;
public:
    void addObserver(Observer* o) { this->list.push_back(o); }
    void notify();
};


#endif //TASK_MANAGER_OBSERVER_H
