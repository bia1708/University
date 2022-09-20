#include "UserService.h"
#include "HTMLRepository.h"
#include "CSVRepository.h"
#include "exceptions.h"
#include <iostream>
#include <cassert>
#include <algorithm>

UserService::UserService(Repository &repository, Repository *interest_list, int currentEventPosition): repository{ repository }, interest_list{ interest_list },
                                                                                                       currentEventsByMonth{}, currentEventPosition { currentEventPosition } {}

int UserService::addInterest(Event e){
    if (this->interest_list->addEvent(e) == 1) {
        int ePos = this->repository.getPos(e);
        int currentNumber = this->repository.getAllEvents()[ePos].getNumberOfPeople();
        this->repository.getAllEvents()[ePos].setNumberOfPeople(currentNumber + 1);
        return 1;
    }
    return 0;
}

int UserService::deleteInterest(const std::string& title){
    Event e {title, "", {0, 0, 0, 0, 0}, 0, ""};
    if (this->interest_list->deleteEvent(e) == 1){
        int ePos = this->repository.getPos(e);
        int currentNumber = this->repository.getAllEvents()[ePos].getNumberOfPeople();
        this->repository.getAllEvents()[ePos].setNumberOfPeople(currentNumber - 1);
        return 1;
    }
    return 0;
}

void UserService::clearEvents(){
    this->currentEventsByMonth.clear();
}

int UserService::filterByMonth(int month){
    this->clearEvents();
//    if (month == 0){
//        for (int i = 0; i < this->repository.repoSize(); i++)
//            this->currentEventsByMonth.push_back(this->repository.getAllEvents()[i]);
//    }
//    else {
//        for (int i = 0; i < this->repository.repoSize(); i++) {
//            if (this->repository.getAllEvents()[i].getDate().month == month)
//                this->currentEventsByMonth.push_back(this->repository.getAllEvents()[i]);
//        }
//    }

    if(month == 0){
        std::vector<Event> events = this->repository.getAllEvents();
        std::copy(events.begin(), events.end(), std::back_inserter(this->currentEventsByMonth));
    } else {
        std::vector<Event> events = this->repository.getAllEvents();
        std::copy_if(events.begin(), events.end(), std::back_inserter(this->currentEventsByMonth), [&month](const Event& e){return e.getDate().month == month;});
    }

    if (this->currentEventsByMonth.empty())
        return -1;
    this->currentEventPosition = 0;
    return 1;
}

std::vector<Event>UserService::getInterests(){
    return this->interest_list->getAllEvents();
}

void UserService::goToNextEvent()
{
    this->currentEventPosition++;
    if(this->currentEventPosition == currentEventsByMonth.size())
        this->currentEventPosition = 0;
}


void UserService::repositoryType(const std::string& fileType) {
    if (fileType == "CSV") {
        this->interest_list = new CSVRepository{};
    }else if (fileType == "HTML") {
        this->interest_list = new HTMLRepository{};
    } else {
        std::string error;
        error += std::string("The filename is invalid!");
        if(!error.empty())
            throw AppError(error);
    }
}

std::vector<Event>UserService::getEventsByMonth(){
    return this->currentEventsByMonth;
}

Event UserService::getCurrentEvent()
{
    return currentEventsByMonth[currentEventPosition];
}

void UserService::openInterestListInApp() {
    std::cout<<"Opening app...";
    this->interest_list->openInApp();
}

std::vector<int> UserService::getAllMonths() {
    std::vector<int> months;
    for (auto &event: this->repository.getAllEvents()) {
        months.emplace_back(event.getMonth());
    }
    std::sort(months.begin(), months.end());
    months.erase(std::unique(months.begin(), months.end()), months.end());
    return months;
}
