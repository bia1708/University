#pragma once
#include <string>
#include <cassert>

struct Date {
	int day, month, year, hour, minute;
};

class Event {
private:
	std::string title;
	std::string description;
	Date date;
	int number_of_people;
	std::string link;

public:
	// constructor
	Event(const std::string& title = "", const std::string& description = "", struct Date date = { 0, 0, 0, 0, 0 }, int number_of_people = 0, const std::string& link = "");
	// copy constructor
	Event(const Event& e);

	void setTitle(const std::string& title);
	void setDescription(const std::string& desccription);
	void setDate(Date date);
	void setNumberOfPeople(int number_of_people);
	void setLink(const std::string& link);

	const std::string& getTitle() const;
	const std::string& getDescription() const;
	struct Date getDate() const;
    int getMonth() const;
	int getNumberOfPeople() const;
	const std::string& getLink() const;

	std::string getOutputFormat() const;

}; 

void testDomain();