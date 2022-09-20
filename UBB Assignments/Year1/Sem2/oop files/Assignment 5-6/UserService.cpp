#include "UserService.h"
#include <iostream>
#include <cassert>

UserService::UserService(Repository &repository, Repository &interest_list, int currentEventPosition): repository{ repository }, interest_list{ interest_list },
                                                                                                       currentEventsByMonth{}, currentEventPosition { currentEventPosition } {}

int UserService::addInterest(Event e){
    if (this->interest_list.addEvent(e) == 1) {
        int ePos = this->repository.getPos(e);
        int currentNumber = this->repository.getAllEvents()[ePos].getNumberOfPeople();
        this->repository.getAllEvents()[ePos].setNumberOfPeople(currentNumber + 1);
        return 1;
    }
    return 0;
}

int UserService::deleteInterest(const std::string& title){
    Event e {title, "", {0, 0, 0, 0, 0}, 0, ""};
    if (this->interest_list.deleteEvent(e) == 1){
        int ePos = this->repository.getPos(e);
        int currentNumber = this->repository.getAllEvents()[ePos].getNumberOfPeople();
        this->repository.getAllEvents()[ePos].setNumberOfPeople(currentNumber - 1);
        return 1;
    }
    return 0;
}

void UserService::clearEvents(){
    for (int i = 0; i <= this->currentEventsByMonth.getSize(); i++)
        this->currentEventsByMonth.remove(this->currentEventsByMonth[i]);
}

int UserService::filterByMonth(int month){
    this->clearEvents();
    if (month == 0){
        for (int i = 0; i < this->repository.repoSize(); i++)
            this->currentEventsByMonth.add(this->repository.getAllEvents()[i]);
    }
    else {
        for (int i = 0; i < this->repository.repoSize(); i++) {
            if (this->repository.getAllEvents()[i].getDate().month == month)
                this->currentEventsByMonth.add(this->repository.getAllEvents()[i]);
        }
    }
    if (this->currentEventsByMonth.getSize() == 0)
        return -1;
    this->currentEventPosition = 0;
    return 1;
}

DynamicVector<Event>UserService::getInterests(){
    return this->interest_list.getAllEvents();
}

void UserService::goToNextEvent()
{
    this->currentEventPosition++;
    if(this->currentEventPosition == currentEventsByMonth.getSize())
        this->currentEventPosition = 0;
}

Event UserService::getCurrentEvent()
{
    return currentEventsByMonth[currentEventPosition];
}

void testUserService(){
    Repository repo1{}, repo2{};
    UserService serv{repo1, repo2};

    // test add
    Date date{ 12, 3, 2021, 14, 30 };
    Event e1{"Party1", "Descr1", date, 100, "link"};
    repo1.addEvent(e1);
    assert(serv.addInterest(e1) == 1);
    assert(serv.addInterest(e1) == 0);
    assert(serv.filterByMonth(3) == 1);
    assert(serv.getCurrentEvent().getOutputFormat() == e1.getOutputFormat());

    Event e2{"Party2", "Descr1", date, 100, "link"};
    repo1.addEvent(e2);
    assert(serv.addInterest(e2) == 1);
    assert(serv.filterByMonth(3) == 1);
    serv.goToNextEvent();
    assert(serv.getCurrentEvent().getOutputFormat() == e2.getOutputFormat());
    serv.goToNextEvent();
    assert(serv.getCurrentEvent().getOutputFormat() == e1.getOutputFormat());

    // test delete
    assert(serv.deleteInterest("Party1") == 1);
    assert(serv.getInterests().getSize() == 1);
    assert(serv.deleteInterest("None") == 0);
    assert(serv.filterByMonth(11) == -1);
    assert(serv.filterByMonth(0) == 1);
}
