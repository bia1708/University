#include "AdministratorService.h"

//AdminService constructor
AdminService::AdminService(Repository& repository) :repository{ repository } {}

int AdminService::adminAddEvent(const std::string& title, const std::string& description, struct Date date, int number_of_people, const std::string& link)
{
	Event eventUsed{ title, description, date, number_of_people, link };
	return repository.addEvent(eventUsed);
}


/*
	Delete an event from the list, by its title
*/
int AdminService::adminDeleteEvent(const std::string& title)
{
	Event eventUsed {title, "", {0, 0, 0, 0, 0}, 0, ""};
	return repository.deleteEvent(eventUsed);
}


int AdminService::adminUpdateEvent(const std::string& title, const std::string& description, struct Date date, int number_of_people, const std::string& link)
{
	Event eventUsed{ title, description, date, number_of_people, link };
	return repository.updateEvent(eventUsed);
}

//Return the list of events
std::vector<Event> AdminService::adminGetEventList()
{
	return repository.getAllEvents();
}

//
//void AdminService::adminPopulateList() {
//	Date date{ 12, 3, 2021, 14, 30 };
//	adminAddEvent("Party1", "Descr1", date, 100, "https://www.google.com");
//
//	date = { 14, 5, 2022, 11, 30 };
//	adminAddEvent("Party2", "Descr2", date, 200, "link");
//
//	date = { 15, 2, 2021, 15, 30 };
//	adminAddEvent("Party3", "Descr3", date, 300, "link");
//
//	date = { 12, 3, 2021, 14, 30 };
//	adminAddEvent("Party4", "Descr4", date, 230, R"(https://www.facebook.com/events/1012427502726506/?acontext=%7B"event_action_history"%3A[%7B"surface"%3A"page"%7D]%7D)");
//
//	date = { 12, 3, 2021, 14, 30 };
//	adminAddEvent("Party5", "Descr5", date, 120, "link");
//
//	date = { 14, 5, 2022, 11, 30 };
//	adminAddEvent("Party6", "Descr6", date, 200, "link");
//
//	date = { 15, 2, 2021, 15, 30 };
//	adminAddEvent("Party7", "Descr7", date, 300, "link");
//
//	date = { 12, 3, 2021, 14, 30 };
//	adminAddEvent("Party8", "Descr8", date, 230, "link");
//
//	date = { 12, 3, 2021, 14, 30 };
//	adminAddEvent("Party9", "Descr9", date, 120, "link");
//
//	date = { 12, 3, 2021, 14, 30 };
//	adminAddEvent("Party10", "Descr10", date, 120, "link");
//}
