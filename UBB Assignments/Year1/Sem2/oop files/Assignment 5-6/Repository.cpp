#include "Repository.h"
#include <iostream>
#include <cassert>

//Repository constructor
Repository::Repository()
{
    DynamicVector<Event> eventList;
}

//Add given event to list
int Repository::addEvent(const Event& eventToAdd)
{
    auto iteratorWhereEventIsFound = this->eventList.find(eventToAdd);
    if (iteratorWhereEventIsFound != -1)
        return -1;
    // eventList.add(eventToAdd);
    eventList + eventToAdd;
    return 1;
}

//Find an event in the given list
int Repository::findEvent(DynamicVector<Event> listOfEvents, const Event& eventToSearch)
{
    if (listOfEvents.find(eventToSearch) != -1)
        return 1;
    else
        return -1;
}


//Delete an event from the eventList
int Repository::deleteEvent(const Event& eventToDelete)
{
    auto iteratorWhereEventIsFound = eventList.find(eventToDelete);
    if (iteratorWhereEventIsFound == -1)
        return -1;
    eventList.remove(eventToDelete);
    return 1;
}


//Update an event from the eventList
int Repository::updateEvent(const Event& eventToUpdateWith)
{
    auto iteratorWhereEventIsFound = eventList.find(eventToUpdateWith);
    if (iteratorWhereEventIsFound == -1)
        return -1;
    eventList[iteratorWhereEventIsFound] = eventToUpdateWith;
    return 1;
}

int Repository::repoSize() {
    return eventList.getSize();
}

int Repository::getPos(const Event& e){
    return this->eventList.find(e);
}

DynamicVector<Event> Repository::getAllEvents()
{
    return eventList;
}

Repository initTestRepository() {
    Repository repo{};
    Date date{ 12, 3, 2021, 14, 30 };
    Event event{ "Party1", "Descr1", date, 100, "link" };
    repo.addEvent(event);

    date = { 14, 5, 2022, 11, 30 };
    event = { "Party2", "Descr2", date, 200, "link" };
    repo.addEvent(event);

    return repo;
}

void testRepository() {
    Repository repo = initTestRepository();
    //test add
    assert(repo.repoSize() == 2);

    //test delete
    Date date{ 12, 3, 2021, 14, 30 };
    Event event{ "Party1", "Descr1", date, 100, "link" };
    assert(repo.getPos(event) == 0);
    assert(repo.deleteEvent(event));
    assert(repo.repoSize() == 1);

    //test findEvent and getALL
    assert(repo.findEvent(repo.getAllEvents(), event) == -1);

    //test update
    date = { 15, 5, 2027, 20, 30 };
    event = { "Party2", "Descr3", date, 280, "link" };
    assert(repo.updateEvent(event));
    assert(repo.findEvent(repo.getAllEvents(), event) == 1);

    // test resize
    date = { 12, 3, 2021, 14, 30 };
    event = {"Party1", "Descr1", date, 100, "https://www.google.com"};
    repo.addEvent(event);
    repo.addEvent(event);
    repo.addEvent(event);
    repo.addEvent(event);
    repo.addEvent(event);
    repo.addEvent(event);
    repo.addEvent(event);
    repo.addEvent(event);
    repo.addEvent(event);
    repo.addEvent(event);
    repo.addEvent(event);
    repo.addEvent(event);
    assert(repo.repoSize() == 13);

    // test add
    DynamicVector<Event> testVector = repo.getAllEvents();
    testVector.add(event);
    assert(testVector.getSize() == 14);

    // test element not found
    event = {"Non", "Descr1", date, 100, "https://www.google.com"};
    assert(testVector.find(event) == -1);
    testVector.remove(event);
    assert(repo.deleteEvent(event) == -1);
    assert(testVector.getSize() == 14);

    // test add resize
    testVector.add(event);
    testVector.add(event);
    testVector.add(event);
    testVector.add(event);
    testVector.add(event);
    testVector.add(event);
    testVector.add(event);
    assert(testVector.getSize() == 21);
}