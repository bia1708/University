//
// Created by bia on 02/07/2022.
//

#ifndef WAZE_REPORT_H
#define WAZE_REPORT_H
#include <string>
#include "Driver.h"

class Report {
private:
    std::string description, reporter;
    location location;
    bool validated;
    int value;
public:
    Report(const std::string &description, const std::string &reporter, const struct location &location, bool validated);

    const std::string &getDescription() const;

    void setDescription(const std::string &description);

    const std::string &getReporter() const;

    void setReporter(const std::string &reporter);

    const struct location &getLocation() const;

    void setLocation(const struct location &location);

    bool isValidated() const;

    int getValue() const;

    void setValue(int value);

    void setValidated(bool validated);
};


#endif //WAZE_REPORT_H
