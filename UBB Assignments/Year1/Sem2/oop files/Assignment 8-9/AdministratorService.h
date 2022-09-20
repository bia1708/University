#pragma once
#include "Repository.h"

class AdminService {
private:
    Repository& repository;

public:
    explicit AdminService(Repository& repository);
    int adminAddEvent(const std::string& title, const std::string& description, struct Date date, int number_of_people, const std::string& link);
    int adminDeleteEvent(const std::string& title);
    int adminUpdateEvent(const std::string& title, const std::string& description, struct Date date, int number_of_people, const std::string& link);
    std::vector<Event> adminGetEventList();
    void adminPopulateList();
};

AdminService initTestService();
void testAdminService();