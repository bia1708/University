//
// Created by bia on 12/05/2022.
//
#include <fstream>
#include "CSVRepository.h"


CSVRepository::CSVRepository() : Repository(this->eventFileName) {
}


CSVRepository::~CSVRepository()
{
}

void CSVRepository::saveToFile()
{
    std::ofstream f(R"(C:\Users\PC\Documents\GitHub\a8-9-bia1708\wishlist.csv)");
    for (auto i : this->eventList) {
        f << i << "\n";
    }
    f.close();
}


//Add given event to list
int CSVRepository::addEvent(const Event& eventToAdd)
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
int CSVRepository::findEvent(std::vector<Event> listOfEvents, const Event& eventToSearch)
{
    if (getPos(eventToSearch) != -1)
        return 1;
    else
        return -1;
}


//Delete an event from the eventList
int CSVRepository::deleteEvent(const Event& eventToDelete)
{
    int iteratorWhereEventIsFound = getPos(eventToDelete);
    if (iteratorWhereEventIsFound == -1)
        return -1;
    this->eventList.erase(this->eventList.begin() + iteratorWhereEventIsFound);
    this->saveToFile();
    return 1;
}


//Update an event from the eventList
int CSVRepository::updateEvent(const Event& eventToUpdateWith)
{
    auto iteratorWhereEventIsFound = getPos(eventToUpdateWith);
    if (iteratorWhereEventIsFound == -1)
        return -1;
    eventList[iteratorWhereEventIsFound] = eventToUpdateWith;
    this->saveToFile();
    return 1;
}

int CSVRepository::repoSize() {
    return this->eventList.size();
}

int CSVRepository::getPos(const Event& e){
    auto pos = std::find_if(this->eventList.begin(), this->eventList.end(), [&e](Event eit){return eit.getTitle() == e.getTitle();});
    if(pos == this->eventList.end())
        return -1;
    return pos - this->eventList.begin();
}

std::vector<Event> CSVRepository::getAllEvents()
{
    return eventList;
}

void CSVRepository::openInApp() {
    system(R"(explorer.exe C:\Users\PC\Documents\GitHub\a8-9-bia1708\wishlist.csv)");
}

