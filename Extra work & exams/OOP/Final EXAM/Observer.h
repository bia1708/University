//
// Created by bia on 06/07/2022.
//

#ifndef E_RETAKE_BIA1708_OBSERVER_H
#define E_RETAKE_BIA1708_OBSERVER_H

#include <vector>
class Observer {
public:
    virtual void update()=0;
};

class Subject {
private:
    std::vector<Observer*> list;
public:
    void addObserver(Observer* o) { this->list.push_back(o); }
    void notify();
};

#endif //E_RETAKE_BIA1708_OBSERVER_H
