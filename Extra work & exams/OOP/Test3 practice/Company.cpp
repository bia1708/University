//
// Created by bia on 05/05/2022.
//

#include "Company.h"

double Company::totalIncome(){
    return this->income + this->moneyFromInvestments;
}

std::string Company::toString() {
    std::string str;
    str = "Name: " + this->name + " || Income: " + std::to_string(this->income) + " || Money From Investments: " +
            std::to_string(this->moneyFromInvestments);
    return str;
}

bool Company::isInterested(Dwelling d) {
    return d.getPrice() / 100 <= this->totalIncome() && d.isProfitable1();
}
