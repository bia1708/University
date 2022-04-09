//
// Created by bia on 06/04/2022.
//

#include "Repository.h"

Repository::Repository() {
    std::vector<Player> playerList;
}

int Repository::addPlayer(Player &player) {
    int position = findPlayer(this->playerList, player);
    if (position == -1)
        return -1;

    this->playerList.push_back(player);
    return 1;
}

int Repository::deletePlayer(Player &player) {
    int position = findPlayer(this->playerList, player);
    if (position == -1)
        return -1;

    this->playerList.erase(this->playerList.begin() + position - 1);
    return 1;
}

int Repository::updatePlayer(Player &newPlayer) {
    int position = findPlayer(this->playerList, newPlayer);
    if (position == -1)
        return -1;

    this->playerList[position] = newPlayer;
    return 1;
}

int Repository::findPlayer(std::vector<Player>thisList, const Player &player) {
    for(int i = 0; i < thisList.size(); i++) {
        if (thisList[i].getName() == player.getName())
            return i;
    }
    return -1;
}

std::vector<Player> Repository::getAllPlayers() {
    return this->playerList;
}

int Repository::repoSize() {
    return this->playerList.size();
}

Repository::~Repository() {
    this->playerList.clear();
}

