#pragma once
#include <string>
#include <cassert>
#include <iostream>
#include <vector>

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
	explicit Event(const std::string& title = "", const std::string& description = "", struct Date date = { 0, 0, 0, 0, 0 }, int number_of_people = 0, const std::string& link = "");
	// copy constructor
	Event(const Event& e);

	void setTitle(const std::string& title);
	void setDescription(const std::string& description);
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

    bool operator==(const Event& eventToCheck) const;
    void operator=(const Event& eventToGetValuesFrom);
    bool operator!=(const Event& eventToCheck) const;
    friend std::ostream& operator<< (std::ostream& outStream, const Event& eventToOutput);
    friend std::istream& operator>> (std::istream& inStream, Event& event);


};
std::string getStringFromDate(Date d);
const std::vector<std::string> explode(const std::string& stringToExplode, const std::string& separatorsUsed);