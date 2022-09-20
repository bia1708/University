//
// Created by bia on 06/04/2022.
//

#include "Domain.h"

Player::Player(const std::string& name, const std::string& nationality, const std::string& team, int goalsScored): name(name), nationality(nationality), team(team), goalsScored(goalsScored){}

Player::Player(Player &p): name(p.name), nationality(p.nationality), team(p.team), goalsScored(p.goalsScored) {}

void Player::setName(const std::string &newName) {
    this->name = newName;
}

void Player::setNationality(const std::string &newNationality) {
    this->nationality = newNationality;
}

void Player::setTeam(const std::string &newTeam) {
    this->team = newTeam;
}

void Player::setGoals(int newGoals) {
    this->goalsScored = newGoals;
}

const std::string& Player::getName() const {
    return this->name;
}

const std::string& Player::getNationality() const {
    return this->nationality;
}

const std::string& Player::getTeam() const {
    return this->team;
}

int Player::getGoals() const {
    return this->goalsScored;
}

std::string Player::getOutputFormat() const {
    std::string output = this->name + " | " + this->nationality + " | " + this->team + " | " + std::to_string(this->goalsScored);
    return output;
}


