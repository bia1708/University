#include "Repository.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <fstream>

//Repository constructor
Repository::Repository(const std::string& eventFileName)
{
    std::vector<Event> eventList;
    this->eventFileName = eventFileName;
//    loadEventsFromFile();
}

void Repository::loadEventsFromFile()
{
    if (this->eventFileName.empty())
        return;
    Event eventLoadedFromFile;
    std::ifstream fin(this->eventFileName);

    while (fin >> eventLoadedFromFile) {
        if(std::find(this->eventList.begin(), this->eventList.end(), eventLoadedFromFile) == this->eventList.end())
            this->eventList.push_back(eventLoadedFromFile);
    }
    fin.close();
}

Repository::~Repository(){
}


//Add given event to list
int Repository::addEvent(const Event& eventToAdd)
{
    auto iteratorWhereEventIsFound = getPos(eventToAdd);
    if (iteratorWhereEventIsFound != -1)
        return -1;
    // eventList.add(eventToAdd);
    eventList.push_back(eventToAdd);
    this->saveToFile();
    return 1;
}

//Find an event in the given list
int Repository::findEvent(std::vector<Event> listOfEvents, const Event& eventToSearch)
{
    if (getPos(eventToSearch) != -1)
        return 1;
    else
        return -1;
}


//Delete an event from the eventList
int Repository::deleteEvent(const Event& eventToDelete)
{
    int iteratorWhereEventIsFound = getPos(eventToDelete);
    if (iteratorWhereEventIsFound == -1)
        return -1;
    this->eventList.erase(this->eventList.begin() + iteratorWhereEventIsFound);
    this->saveToFile();
    return 1;
}


//Update an event from the eventList
int Repository::updateEvent(const Event& eventToUpdateWith)
{
    auto iteratorWhereEventIsFound = getPos(eventToUpdateWith);
    if (iteratorWhereEventIsFound == -1)
        return -1;
    eventList[iteratorWhereEventIsFound] = eventToUpdateWith;
    this->saveToFile();
    return 1;
}

int Repository::repoSize() {
    return this->eventList.size();
}

int Repository::getPos(const Event& e){
    auto pos = std::find_if(this->eventList.begin(), this->eventList.end(), [&e](Event eit){return eit.getTitle() == e.getTitle();});
    if(pos == this->eventList.end())
        return -1;
    return pos - this->eventList.begin();
}

std::vector<Event> Repository::getAllEvents()
{
    return eventList;
}

void Repository::saveToFile() {
}

void Repository::openInApp() {

}
