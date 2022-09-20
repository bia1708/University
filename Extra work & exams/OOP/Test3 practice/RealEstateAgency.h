//
// Created by bia on 05/05/2022.
//

#include "Dwelling.h"
#include "Client.h"
#include <iostream>
#include <vector>

class RealEstateAgency {
private:
    std::vector<Client*> clientsArray;
    std::vector<Dwelling*> dwellingsArray;

public:
    Dwelling* addDwelling(double price, bool isProfitable);
    void removeClient(const std::string& name);
    std::vector<Client> getInterested(Dwelling d);
    void writeToFile(const std::string& filename);
};

