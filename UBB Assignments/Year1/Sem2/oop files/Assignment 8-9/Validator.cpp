//
// Created by bia on 12/05/2022.
//
#include "Validator.h"



Validator::Validator()
{
}


Validator::~Validator()
{
}

void Validator::validateEvent(const Event &event)
{
    std::vector<std::string> errors;
    if (event.getTitle().size() < 1)
        errors.push_back("	The title name cannot be less than 1 characters!\n");
    if (event.getDate().year < 1889 || event.getDate().year > 2100)
        errors.push_back(std::string("	Year has to be an integer greater than 1889 and smaller than 2100!\n"));

    // search for "www" at the beginning of the source string
    int posWww = event.getLink().find("www");
    if (posWww != 0)
        errors.push_back("	The link must start with the following string: \"www\" \n");

    if (errors.size() > 0)
        throw EventException(errors);
}


EventException::EventException(std::vector<std::string> _errors) {
    this->errors = _errors;
}

std::vector<std::string> EventException::getErrors() const
{
    return this->errors;
}