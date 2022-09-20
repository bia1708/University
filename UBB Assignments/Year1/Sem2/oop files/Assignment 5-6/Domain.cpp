#include "Domain.h"
#include <iostream>
#include <cassert>

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
	std::string output = "Event Title: " + title + " || Description: " + description + " || Date and time: " + std::to_string(date.day) + "-" \
		+ std::to_string(date.month) + "-" + std::to_string(date.year) + " " + std::to_string(date.hour) + ":" + std::to_string(date.minute) + \
		" || Number of people: " + std::to_string(number_of_people) + " || Link: " + link;
	return output;
}

void testDomain() {
	Date date{ 12, 3, 2021, 14, 30 };
	Event event{ "Party1", "Descr1", date, 100, "link" };

    assert(event.getOutputFormat() == "Event Title: Party1 || Description: Descr1 || Date and time: 12-3-2021 14:30 || Number of people: 100 || Link: link");

    assert(event.getDate().day == date.day);
	assert(event.getTitle() == "Party1");
	assert(event.getDescription() == "Descr1");
	assert(event.getNumberOfPeople() == 100);
	assert(event.getLink() == "link");

    Date newDate {13, 10, 2021, 15, 50};
    event.setDate(newDate);
    assert(event.getDate().day == newDate.day);

    event.setTitle("Party2");
    assert(event.getTitle() == "Party2");

    event.setDescription("Descr2");
    assert(event.getDescription() == "Descr2");

    event.setNumberOfPeople(200);
    assert(event.getNumberOfPeople() == 200);

    event.setLink("link2");
    assert(event.getLink() == "link2");

    Event event2 = event;
    assert(event2.getTitle() == event.getTitle());
}