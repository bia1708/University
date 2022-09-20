//
// Created by bia on 05/07/2022.
//

#ifndef QNA_OBSERVER_H
#define QNA_OBSERVER_H

#include <vector>

class Observer {
public:
    virtual void update()=0;
};

class Subject {
private:
    std::vector<Observer*> list;
public:
    void addObserver(Observer* o) { this->list.push_back(o); };
    void notify();

};

#endif //QNA_OBSERVER_H
