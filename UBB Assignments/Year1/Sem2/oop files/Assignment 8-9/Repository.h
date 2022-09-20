#pragma once

#include "Domain.h"
#include <vector>
#include <algorithm>
#include "DynamicArray.h"


class Repository
{
protected:
    std::vector<Event> eventList;
    std::string eventFileName;

public:
    Repository(const std::string& eventFileName);
    ~Repository();

    virtual void saveToFile();
    void loadEventsFromFile();
//    void writeToFile();

    virtual int addEvent(const Event& eventToAdd);
    virtual int findEvent(std::vector<Event> listOfEvents, const Event& eventToSearch);
    virtual int deleteEvent(const Event& eventToDelete);
    virtual int updateEvent(const Event& eventToUpdateWith);

    virtual std::vector<Event> getAllEvents();
    virtual int getPos(const Event& e);
    virtual int repoSize();
    virtual void openInApp();
};


