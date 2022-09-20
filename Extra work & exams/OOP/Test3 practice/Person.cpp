//
// Created by bia on 05/05/2022.
//

#include "Person.h"

bool Person::isInterested(Dwelling d) {
    return d.getPrice() / 1000 <= this->totalIncome();
}
