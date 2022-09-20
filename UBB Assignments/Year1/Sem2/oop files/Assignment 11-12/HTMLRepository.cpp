//
// Created by bia on 11/05/2022.
//
#include "HTMLRepository.h"
#include <Windows.h>
#include <shellapi.h>
#include <fstream>


HTMLRepository::HTMLRepository(): Repository(this->eventFileName){}


HTMLRepository::~HTMLRepository() {

}

void HTMLRepository::saveToFile()
{
    std::ofstream f(R"(C:\Users\PC\Documents\GitHub\a8-9-bia1708\wishlist.html)");

    f << "<!DOCTYPE html>" << "\n";
    f << "<html>" << "\n";

    f << "<head>" << "\n";
    f << "<title>Movie Playlist</title>" << "\n";
    f << "</head>" << "\n";

    f << "<body>" << "\n";

    f << "<table border=\"1\">" << "\n";

    f << "<tr>" << "\n";
    f << "<td>Title</td>" << "\n";
    f << "<td>Genre</td>" << "\n";
    f << "<td>Year</td>" << "\n";
    f << "<td>Likes</td>" << "\n";
    f << "<td>Trailer</td>" << "\n";
    f << "</tr>" << "\n";

    for (const auto& i : this->getAllEvents())
    {
        f << "<tr>" << "\n";

        f << "<td>" << i.getTitle() << "</td>" << "\n";
        f << "<td>" << i.getDescription() << "</td>" << "\n";
        f << "<td>" << i.getDate().year << "</td>" << "\n";
        f << "<td>" << i.getDate().month << "</td>" << "\n";
        f << "<td>" << i.getDate().day << "</td>" << "\n";
        f << "<td>" << i.getDate().hour<< "</td>" << "\n";
        f << "<td>" << i.getDate().minute << "</td>" << "\n";
        f << "<td>" << i.getNumberOfPeople() << "</td>" << "\n";
        f << "<td><a href =" << i.getLink() << ">Link</a></td>";

        f << "</tr>" << "\n";
    }

    f << "</table>" << "\n";

    f << "</body>" << "\n";

    f << "</html>" << "\n";
    f.close();

}


//Add given event to list
int HTMLRepository::addEvent(const Event& eventToAdd)
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
int HTMLRepository::findEvent(std::vector<Event> listOfEvents, const Event& eventToSearch)
{
    if (getPos(eventToSearch) != -1)
        return 1;
    else
        return -1;
}


//Delete an event from the eventList
int HTMLRepository::deleteEvent(const Event& eventToDelete)
{
    int iteratorWhereEventIsFound = getPos(eventToDelete);
    if (iteratorWhereEventIsFound == -1)
        return -1;
    this->eventList.erase(this->eventList.begin() + iteratorWhereEventIsFound);
    this->saveToFile();
    return 1;
}


//Update an event from the eventList
int HTMLRepository::updateEvent(const Event& eventToUpdateWith)
{
    auto iteratorWhereEventIsFound = getPos(eventToUpdateWith);
    if (iteratorWhereEventIsFound == -1)
        return -1;
    eventList[iteratorWhereEventIsFound] = eventToUpdateWith;
    this->saveToFile();
    return 1;
}

int HTMLRepository::repoSize() {
    return this->eventList.size();
}

int HTMLRepository::getPos(const Event& e){
    auto pos = std::find_if(this->eventList.begin(), this->eventList.end(), [&e](Event eit){return eit.getTitle() == e.getTitle();});
    if(pos == this->eventList.end())
        return -1;
    return pos - this->eventList.begin();
}

std::vector<Event> HTMLRepository::getAllEvents()
{
    return eventList;
}

void HTMLRepository::openInApp() {
    system(R"(explorer.exe C:\Users\PC\Documents\GitHub\a8-9-bia1708\wishlist.html)");
}

