//
// Created by bia on 05/05/2022.
//
#include "Dwelling.h"
#include "Client.h"

class Person :public Client{
public:
    bool isInterested(Dwelling d) override;
};
