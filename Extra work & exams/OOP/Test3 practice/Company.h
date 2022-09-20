//
// Created by bia on 05/05/2022.
//
#include <iostream>
#include "Dwelling.h"
#include "Client.h"

class Company : public Client{
private:
    double moneyFromInvestments;
public:
    double totalIncome() override;
    std::string toString() override;
    bool isInterested(Dwelling d) override;
};
