#include "Domain.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

// default constructor
Event::Event(const std::string& title, const std::string& description, struct Date date, int number_of_people, const std::string& link) : title(title), description(description), date(date), number_of_people(number_of_people), link(link) {}

// copy constructor
Event::Event(const Event& old_event) : title(old_event.title), description(old_event.description), date(old_event.date), number_of_people(old_event.number_of_people), link(old_event.link){}

//	SETTERS
void Event::setTitle(const std::string& title) {
	Event::title = title;
}

void Event::setDescription(const std::string& description) {
	Event::description = description;
}

void Event::setDate(Date date) {
	Event::date = date;
}

void Event::setNumberOfPeople(int number_of_people) {
	Event::number_of_people = number_of_people;
}

void Event::setLink(const std::string& link) {
	Event::link = link;
}

// GETTERS
const std::string& Event::getTitle() const {
	return title;
}

const std::string& Event::getDescription() const {
	return description;
}

struct Date Event::getDate() const {
	return date;
}

int Event::getNumberOfPeople() const {
	return number_of_people;
}

const std::string& Event::getLink() const {
	return link;
}

std::string Event::getOutputFormat() const {
	std::string output = "Event Title:" + title + "|| Description:" + description + "|| Date and time:" + std::to_string(date.day) + "-" \
		+ std::to_string(date.month) + "-" + std::to_string(date.year) + "-" + std::to_string(date.hour) + "-" + std::to_string(date.minute) + \
		"|| Number of people:" + std::to_string(number_of_people) + "|| Link:" + link;
	return output;
}


bool Event::operator==(const Event& eventToCheck) const
{
    return this->title == eventToCheck.title;
}

void Event::operator=(const Event& eventToGetValuesFrom)
{
    title = eventToGetValuesFrom.getTitle();
    description = eventToGetValuesFrom.getDescription();
    date = eventToGetValuesFrom.getDate();
    number_of_people = eventToGetValuesFrom.getNumberOfPeople();
    link = eventToGetValuesFrom.getLink();
}

bool Event::operator!=(const Event& eventToCheck) const
{
    return !(eventToCheck == *this);
}


std::ostream& operator<< (std::ostream& outStream, const Event& eventToOutput) {
    outStream << eventToOutput.getOutputFormat();
    return outStream;
}

std::istream& operator>> (std::istream& inStream, Event& event) {
    std::string eventString;
    std::getline(inStream, eventString);
    if(eventString.empty()){
        inStream.setstate(std::ios::failbit);
        return inStream;
    }
    std::vector <std::string> tokens;
    if (eventString.empty()) {
        return inStream;
    }
    tokens = explode(eventString, "|:-");
    event.setTitle(tokens[0].substr(1));
    event.setDescription(tokens[1].substr(1));
    Date date{std::stoi(tokens[2].substr(1)), std::stoi(tokens[3].substr(1)), std::stoi(tokens[4].substr(1)), std::stoi(tokens[5].substr(1)), std::stoi(tokens[6].substr(1))};
    event.setDate(date);
    event.setNumberOfPeople(std::stoi(tokens[7].substr(1)));
    event.setLink(tokens[8].substr(1));
    return inStream;
}

const std::vector<std::string>explode(const std::string& stringToExplode, const std::string& separatorsUsed)
{
    std::vector<std::string>trashValues = { "Event Title", " Description", " Date and time", " Number of people", " Link" };
    std::string partialStringObtained;
    std::vector<std::string> explodedString;

    for (auto iterator : stringToExplode)
    {
        if (iterator != separatorsUsed[0] && iterator != separatorsUsed[1] && iterator != separatorsUsed[2])
            partialStringObtained += iterator;
        else
        if ((iterator == separatorsUsed[0] || iterator == separatorsUsed[1] || iterator == separatorsUsed[2]) && !partialStringObtained.empty()) {
            if (find(trashValues.begin(), trashValues.end(), partialStringObtained) == trashValues.end()) {
                explodedString.push_back(partialStringObtained);
            }
            partialStringObtained = "";
        }
    }
    if (!partialStringObtained.empty())
        explodedString.push_back(partialStringObtained);
    return explodedString;
}