//
// Created by bia on 06/04/2022.
//

#include "Service.h"

Service::Service(Repository &repo) : repo(repo) {}

int Service::addPlayer(std::string &name, std::string &nationality, std::string &team, int goals) {
    if (nationality.size() != 3)
        return -1;
    Player player{name, nationality, team, goals};
    return this->repo.addPlayer(player);
}
