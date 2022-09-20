//
// Created by bia on 02/07/2022.
//

#include "Report.h"

Report::Report(const std::string &description, const std::string &reporter, const struct location &location,
               bool validated) : description(description), reporter(reporter), location(location),
                                 validated(validated) {
    if(validated)
        value = 2;
    else value = 0;
}

const std::string &Report::getDescription() const {
    return description;
}

void Report::setDescription(const std::string &description) {
    Report::description = description;
}

const std::string &Report::getReporter() const {
    return reporter;
}

void Report::setReporter(const std::string &reporter) {
    Report::reporter = reporter;
}

const struct location &Report::getLocation() const {
    return location;
}

void Report::setLocation(const struct location &location) {
    Report::location = location;
}

bool Report::isValidated() const {
    return validated;
}

void Report::setValidated(bool validated) {
    Report::validated = validated;
}

int Report::getValue() const {
    return value;
}

void Report::setValue(int value) {
    Report::value = value;
}
