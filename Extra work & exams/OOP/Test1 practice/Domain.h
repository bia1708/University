//
// Created by bia on 06/04/2022.
//

#pragma once
#include <string>

class Player{
private:
    std::string name, nationality, team;
    int goalsScored;

public:
    // constructor
    explicit Player(const std::string& name = "", const std::string& nationality = "", const std::string& team = "", int goalsScored = 0);

    // copy constructor
    Player(Player& p);

    // setters
    void setName(const std::string& newName);
    void setNationality(const std::string& newNationality);
    void setTeam(const std::string& newTeam);
    void setGoals(int newGoals);

    // getters
    const std::string& getName() const;
    const std::string& getNationality() const;
    const std::string& getTeam() const;
    int getGoals() const;

    // output format
    std::string getOutputFormat() const;
};