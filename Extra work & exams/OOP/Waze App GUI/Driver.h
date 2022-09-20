//
// Created by bia on 02/07/2022.
//

#ifndef WAZE_DRIVER_H
#define WAZE_DRIVER_H

#include <string>

struct location{
    int lat, lng;
};

class Driver {
private:
    std::string name, status;
    struct location location;
    int score;
public:
    Driver(const std::string &name, const std::string &status, struct location &location, int score);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getStatus() const;

    void setStatus(const std::string &status);

    const struct location &getLocation() const;

    void setLocation(const struct location &location);

    int getScore() const;

    void setScore(int score);

};


#endif //WAZE_DRIVER_H
