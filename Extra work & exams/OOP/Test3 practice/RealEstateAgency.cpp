//
// Created by bia on 05/05/2022.
//

#include "RealEstateAgency.h"
#include <fstream>

Dwelling* RealEstateAgency::addDwelling(double price, bool isProfitable) {
    Dwelling *d = new Dwelling{price, isProfitable};
    this->dwellingsArray.push_back(d);
    return d;
}

void RealEstateAgency::removeClient(const std::string& name) {
    int pos;
    for(int i = 0; i < this->clientsArray.size(); i++)
        if(this->clientsArray[i]->getName() == name) {
            pos = i;
            break;
        }

    this->clientsArray.erase(this->clientsArray.begin() + pos);
}

std::vector<Client> RealEstateAgency::getInterested(Dwelling d) {
    std::vector<Client> solution;
    for(auto & client : this->clientsArray)
        if(client->isInterested(d))
            solution.push_back(*client);
    return solution;
}

void RealEstateAgency::writeToFile(const std::string& filename) {
    std::ofstream file(filename);
    for(auto & client : this->clientsArray){
        file << client->toString() << "\n";
    }
}
