#pragma once

#include "Domain.h"
#include <vector>
#include <algorithm>
#include "DynamicArray.h"


class Repository
{
private:
    DynamicVector<Event> eventList;

public:
    Repository();

    int addEvent(const Event& eventToAdd);
    int findEvent(DynamicVector<Event> listOfEvents, const Event& eventToSearch);
    int deleteEvent(const Event& eventToDelete);
    int updateEvent(const Event& eventToUpdateWith);
    DynamicVector<Event> getAllEvents();
    int getPos(const Event& e);
    int repoSize();
};


void testRepository();