#pragma once
#include "Repository.h"

class UserService{
private:
    Repository& repository;
    Repository& interest_list;
    DynamicVector<Event> currentEventsByMonth;
    int currentEventPosition;

public:
    UserService(Repository& repository, Repository& interests_repo, int currentEventPosition = 0);

    int addInterest(Event e);
    int deleteInterest(const std::string& title);
    int filterByMonth(int month);
    DynamicVector<Event>getInterests();
    void goToNextEvent();
    Event getCurrentEvent();
    void clearEvents();
};

void testUserService();
