//
// Created by bia on 02/07/2022.
//

#ifndef WAZE_OBSERVER_H
#define WAZE_OBSERVER_H

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



#endif //WAZE_OBSERVER_H
