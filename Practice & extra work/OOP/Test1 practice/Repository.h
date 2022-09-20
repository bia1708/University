//
// Created by bia on 06/04/2022.
//
#include "Domain.h"
#include <vector>
class Repository {
private:
    std::vector<Player> playerList;

public:
    // constructor
    Repository();

    // destructor
    virtual ~Repository();

    int addPlayer(Player& player);
    int deletePlayer(Player& player);
    int updatePlayer(Player& newPlayer);
    static int findPlayer(std::vector<Player>thisList, const Player& player);
    std::vector<Player> getAllPlayers();
    int repoSize();
};

