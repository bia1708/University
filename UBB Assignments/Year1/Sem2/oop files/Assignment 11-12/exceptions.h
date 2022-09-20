//
// Created by bia on 19/05/2022.
//

#ifndef A11_12_BIA1708_EXCEPTIONS_H
#define A11_12_BIA1708_EXCEPTIONS_H


#include <exception>
#include <string>

class AppError : public std::exception {
private:
    std::string message;
public:
    explicit AppError(std::string message);
    const char *what() const noexcept override;
    void print_error() const;
};

class EventError : public AppError {
public:
    explicit EventError(std::string message);
};

class RepositoryError : public AppError {
public:
    explicit RepositoryError(std::string message);
};

class ServiceError : public AppError {
public:
    explicit ServiceError(std::string message);
};


#endif //A11_12_BIA1708_EXCEPTIONS_H
