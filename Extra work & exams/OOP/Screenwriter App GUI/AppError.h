//
// Created by bia on 04/07/2022.
//

#ifndef SCREENWRITER_APPERROR_H
#define SCREENWRITER_APPERROR_H

#include <string>

class AppError : public std::exception {
private:
    std::string msg;
public:
    explicit AppError(const std::string &msg) : msg(msg) {}

    std::string what(){
        return this->msg.c_str();
    }
};


#endif //SCREENWRITER_APPERROR_H
