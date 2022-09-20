#pragma once
#include "Repository.h"

class UserService{
private:
    Repository& repository;
    Repository* interest_list;
    std::vector<Event> currentEventsByMonth;
    int currentEventPosition;

public:
    UserService(Repository& repository, Repository* interests_repo, int currentEventPosition = 0);

    int addInterest(Event e);
    int deleteInterest(const std::string& title);
    int filterByMonth(int month);
    std::vector<Event>getInterests();
    void goToNextEvent();
    Event getCurrentEvent();
    void clearEvents();

    void repositoryType(const std::string &fileType);
    void openInterestListInApp();
};

