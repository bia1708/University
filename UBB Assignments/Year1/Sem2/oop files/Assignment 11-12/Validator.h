//
// Created by bia on 12/05/2022.
//
#pragma once
#include "Domain.h"
#include <exception>
#include <vector>

class Validator
{
public:
    Validator();
    ~Validator();

    void validateEvent(const Event &event);
};

class EventException
{
private:
    std::vector<std::string> errors;

public:
    EventException(std::vector<std::string> _errors);
    std::vector<std::string> getErrors() const;
};