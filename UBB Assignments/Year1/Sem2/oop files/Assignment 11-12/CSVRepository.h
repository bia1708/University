//
// Created by bia on 12/05/2022.
//

#pragma once
#include "Repository.h"
class CSVRepository :public Repository{
public:
    CSVRepository();
    ~CSVRepository();

    void saveToFile() override;
    int addEvent(const Event& eventToAdd) override;
    int findEvent(std::vector<Event> listOfEvents, const Event& eventToSearch) override;
    int deleteEvent(const Event& eventToDelete) override;
    int updateEvent(const Event& eventToUpdateWith) override;

    std::vector<Event> getAllEvents() override;
    int getPos(const Event& e) override;
    int repoSize() override;
    void openInApp() override;
};
